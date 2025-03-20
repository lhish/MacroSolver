//
// Created by lhy on 25-3-10.
//
#include "solve_macro.h"

#include <iostream>
#include <sstream>
namespace lhy {
inline std::string_view trim(const std::string_view str) {
  const auto start = str.find_first_not_of(" \t\n\r");
  const auto end = str.find_last_not_of(" \t\n\r");
  if (start == std::string::npos || end == std::string::npos) {
    return "";
  }
  return str.substr(start, end - start + 1);
}
inline std::vector<std::string_view> split(const std::string_view str, char specific_char,
                                           const std::vector<std::pair<char, char>>& ignore_string = {},
                                           int max_split = 1000000) {
  /// 不太记得这个flag是干嘛的了
  std::vector<std::string_view> ret;
  int split_count = 0;
  bool flag = false;
  int start = 0;
  std::vector<char> solve_char;
  for (int i = 0; i < str.length(); i++) {
    auto& each = str[i];
    if (each == '\\') {
      flag = true;
    } else {
      if (flag == false && !solve_char.empty() && each == solve_char.back()) {
        solve_char.pop_back();
      } else if (auto pos = std::ranges::find_if(
                     ignore_string, [&each](const std::pair<char, char>& element) { return element.first == each; });
                 flag == false && pos != ignore_string.end()) {
        solve_char.emplace_back(pos->second);
      } else if (solve_char.empty() && each == specific_char) {
        ret.push_back(str.substr(start, i - start));
        split_count++;
        start = i + 1;
        if (split_count == max_split) {
          ret.emplace_back(str.substr(i + 1, str.length() - i - 1));
          return ret;
        }
        continue;
      }
      flag = false;
    }
  }
  if (start != str.length()) {
    ret.push_back(str.substr(start, str.length() - start));
  }
  if (ret.empty()) {
    ret.push_back(str);
  }
  return ret;
}
void MacroSolver::AddMacro(std::string macro) {
  all_macro_.emplace_back(std::move(macro));
  //  std::cout << "all_macro:" << all_macro_.back() << std::endl;
  std::string_view macro_view = all_macro_.back();
  auto splits = split(macro_view, '(', {}, 1);
  const auto name = split(splits[0], ' ', {}, 1)[1];
  splits = split(splits[1], ')', {}, 1);
  const auto var = splits[0];
  const auto definition = splits[1];
  macro_map_.insert_or_assign(name, std::pair{split(var, ','), definition});
  /// 全部输出
  for (auto& [key, value] : macro_map_) {
    //    std::cout << "name:" << key << std::endl;
    for (auto& each : value.first) {
      each = trim(each);
      //      std::cout << "var:" << each << std::endl;
    }
    //    std::cout << "definition:" << value.second << std::endl;
  }
}
bool MacroSolver::CheckUsed(std::list<std::pair<std::string, std::list<std::string>::iterator>>& used,
                            std::list<std::string>::iterator& iter, std::list<std::string>& tokens) {
  for (auto each_iter = used.begin(); each_iter != used.end();) {
    if (each_iter->second == iter) {
      each_iter = used.erase(each_iter);
    } else {
      ++each_iter;
    }
  }
  if (iter == tokens.end()) {
    return false;
  }
  if (macro_map_.contains(*iter) &&
      std::ranges::find(used, *iter, [](const std::pair<std::string, std::list<std::string>::iterator>& element) {
        return element.first;
      }) != used.end()) {
    *iter += '\n';
    ++iter;
    return true;
  }
  return false;
}
std::list<std::string>::iterator MacroSolver::SolveMacro(
    std::list<std::string>::iterator begin, std::list<std::string>::iterator end, std::list<std::string>& tokens,
    std::list<std::pair<std::string, std::list<std::string>::iterator>> used) {
  auto iter = begin;
  auto iter_ret = begin;
  while (iter != end) {
    if (CheckUsed(used, iter, tokens)) continue;
    if (auto iter_temp = iter; macro_map_.contains(*iter) && (++iter_temp) != end && *iter_temp == "(") {
      int count = 0;
      CheckUsed(used, iter_temp, tokens);
      ++iter_temp;
      while (iter_temp != end) {
        if (CheckUsed(used, iter_temp, tokens)) continue;
        if (*iter_temp == "(") {
          count++;
        } else if (*iter_temp == ")" && count > 0) {
          count--;
        } else if (*iter_temp == ")") {
          break;
        }
        ++iter_temp;
      }
      ++iter_temp;
      bool flag = iter == iter_ret;
      std::string add_used = *iter;
      auto result = Expand(iter, iter_temp, tokens, used);
      std::cout << "Expanding:" << Cat(iter, iter_temp) << '\n';
      auto first_iter = tokens.insert(tokens.erase(iter, iter_temp), result.begin(), result.end());
      std::cout << "Result:" << Cat(tokens.begin(), tokens.end()) << '\n';
      used.emplace_back(add_used, iter_temp);
      iter = first_iter;
      if (flag) {
        iter_ret = iter;
      }
    } else {
      ++iter;
    }
  }
  return iter_ret;
}
std::string MacroSolver::SolveOneMacro(const std::string& macro) {
  auto tokens = GetTokens(macro);
  auto ret = SolveMacro(tokens.begin(), tokens.end(), tokens);
  return Cat(tokens.begin(), tokens.end());
}
void MacroSolver::ClearAllMacro() { macro_map_.clear(); }
std::list<std::string> MacroSolver::Expand(std::list<std::string>::iterator begin, std::list<std::string>::iterator end,
                                           std::list<std::string>& tokens,
                                           std::list<std::pair<std::string, std::list<std::string>::iterator>> used) {
  auto def = macro_map_[*begin];
  std::vector<std::pair<std::list<std::string>::iterator, std::list<std::string>::iterator>> final_var;
  auto iter_start = std::next(begin, 2);
  int count = 0;
  for (auto iter = iter_start; iter != std::prev(end, 1); ++iter) {
    if (count == 0 && *iter == ",") {
      final_var.emplace_back(iter_start, iter);
      iter_start = std::next(iter, 1);
    } else if (*iter == "(") {
      count++;
    } else if (*iter == ")") {
      count--;
    }
  }
  final_var.emplace_back(iter_start, std::prev(end, 1));
  std::vector<std::pair<std::list<std::string>::iterator, std::list<std::string>::iterator>> final_var_solved;
  std::vector<std::list<std::string>> final_var_ori;
  for (auto& [begin_iter, end_iter] : final_var) {
    final_var_ori.emplace_back(begin_iter, end_iter);
    auto first_iter = SolveMacro(begin_iter, end_iter, tokens, used);
    final_var_solved.emplace_back(first_iter, end_iter);
  }
  std::list<std::string> result;
  auto def_definition = GetTokens(std::string(def.second));
  for (auto iter = def_definition.begin(); iter != def_definition.end(); ++iter) {
    auto& each = *iter;
    if (auto the_one = std::ranges::find(def.first, each); the_one != def.first.end()) {
      if (iter != def_definition.begin() && *std::prev(iter) == "#") {
        result.push_back("\"");
        auto& push_element = final_var_ori[the_one - def.first.begin()];
        for (auto& each_push_element : push_element) {
          if (each_push_element == "\"") {
            result.push_back("\\");
          }
          result.push_back(each_push_element);
        }
        result.push_back("\"");
      } else if (iter != def_definition.begin() && *std::prev(iter, 1) == "##") {
        auto& push_element = final_var_ori[the_one - def.first.begin()];
        if (!push_element.empty() && !result.empty() && IsStringNormal(result.back()) &&
            IsStringNormal(push_element.front())) {
          result.back() += push_element.front();
          push_element.pop_front();
        }
        result.insert(result.end(), push_element.begin(), push_element.end());
      } else if (std::next(iter) != def_definition.end() && *std::next(iter) == "##") {
        auto& push_element = final_var_ori[the_one - def.first.begin()];
        result.insert(result.end(), push_element.begin(), push_element.end());
      } else {
        const auto& [push_element_first, push_element_second] = final_var_solved[the_one - def.first.begin()];
        result.insert(result.end(), push_element_first, push_element_second);
      }
    } else if (each == "__VA_OPT__") {
      auto now_iter = std::next(iter, 2);
      int count1 = 0;
      while (now_iter != def_definition.end()) {
        if (*now_iter == "(") {
          count1++;
        } else if (count1 > 0 && *now_iter == ")") {
          count1--;
        } else if (*now_iter == ")") {
          break;
        }
        ++now_iter;
      }
      if (final_var_ori.size() > static_cast<int>(def.first.size()) - 1) {
        int next_num = 2;
        if (!result.empty() && IsStringNormal(result.back()) && IsStringNormal(*std::next(iter, next_num))) {
          result.back() += *std::next(iter, next_num);
          next_num++;
        }
        result.insert(result.end(), std::next(iter, next_num), now_iter);
      }
      iter = now_iter;
    } else if (each == "__VA_ARGS__") {
      std::list<std::string> push_element;
      std::list<std::string> ori_push_element;
      for (int i = static_cast<int>(def.first.size()) - 1; i < final_var_solved.size(); i++) {
        for (auto push_element_iter = final_var_solved[i].first; push_element_iter != final_var_solved[i].second;
             ++push_element_iter) {
          push_element.push_back(*push_element_iter);
        }
        for (auto& each_push_element : final_var_ori[i]) {
          ori_push_element.push_back(each_push_element);
        }
        if (i + 2 <= final_var_solved.size()) {
          push_element.push_back(",");
          ori_push_element.push_back(",");
        }
      }
      if (iter != def_definition.begin() && *std::prev(iter) == "#") {
        result.push_back("\"");
        for (auto& each_push_element : ori_push_element) {
          if (each_push_element == "\"") {
            result.push_back("\\");
          }
          result.push_back(each_push_element);
        }
        result.push_back("\"");
      } else if (iter != def_definition.begin() && std::prev(iter, 1) != def_definition.begin() &&
                 *std::prev(iter, 2) == "," && *std::prev(iter) == "##" && push_element.empty()) {
        result.pop_back();
      } else {
        result.insert(result.end(), push_element.begin(), push_element.end());
      }
    } else {
      if (each != "#" && each != "##") {
        result.push_back(each);
      }
    }
  }
  return result;
}
std::list<std::string> MacroSolver::GetTokens(std::string macro) const {
  std::list<std::string> ret;
  std::string solving{};
  macro += '\t';
  int before_is_normal{};
  for (const auto& each : macro) {
    if ((IsNormal(each) && before_is_normal) || (solving == "#" && each == '#')) {
      solving += each;
    } else {
      if (solving != "") {
        ret.emplace_back(solving);
      }
      solving = "";
      if (each != ' ') {
        solving += each;
      }
    }
    before_is_normal = IsNormal(each);
  }
  return ret;
}
std::string MacroSolver::Cat(const std::list<std::string>::iterator begin,
                             const std::list<std::string>::iterator end) const {
  std::ostringstream oss;
  for (auto iter = begin; iter != end; ++iter) {
    for (const auto& each : *iter) {
      if (each != '\n' && each != '#') {
        oss << each;
      }
    }
    oss << ' ';
  }
  return oss.str();
}
std::string MacroSolver::CatWithUsed(std::list<std::string>::iterator begin,
                                     std::list<std::string>::iterator end) const {
  std::string ret;
  for (auto iter = begin; iter != end; ++iter) {
    for (const auto& each : *iter) {
      ret += each;
    }
  }
  return ret;
}
bool MacroSolver::IsNormal(const char c) {
  static const std::string all_normal = "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_\n";
  return all_normal.find(c) != std::string::npos;
}
bool MacroSolver::IsStringNormal(const std::string& str) {
  for (auto& each : str) {
    if (!IsNormal(each)) {
      return false;
    }
  }
  return true;
}

}  // namespace lhy