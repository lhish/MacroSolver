//
// Created by lhy on 25-3-10.
//

#ifndef SOLVE_MACRO_H
#define SOLVE_MACRO_H
#include <list>
#include <map>
#include <string>
#include <vector>
namespace lhy {
class MacroSolver {
 public:
  static MacroSolver& GetInstance() {
    static MacroSolver macro_solver;
    return macro_solver;
  }
  void AddMacro(std::string macro);
  bool CheckUsed(std::list<std::pair<std::string, std::list<std::string>::iterator>>& used,
                 std::list<std::string>::iterator& iter, std::list<std::string>& tokens);
  [[nodiscard]] std::string SolveOneMacro(const std::string& macro);
  void ClearAllMacro();

 private:
  MacroSolver() = default;

  std::list<std::string>::iterator SolveMacro(
      std::list<std::string>::iterator begin, std::list<std::string>::iterator end, std::list<std::string>& tokens,
      std::list<std::pair<std::string, std::list<std::string>::iterator>> used = {});
  [[nodiscard]] std::list<std::string> Expand(
      std::list<std::string>::iterator begin, std::list<std::string>::iterator end, std::list<std::string>& tokens,
      std::list<std::pair<std::string, std::list<std::string>::iterator>> used = {});
  [[nodiscard]] std::list<std::string> GetTokens(std::string macro) const;
  [[nodiscard]] std::string Cat(std::list<std::string>::iterator begin, std::list<std::string>::iterator end) const;
  [[nodiscard]] std::string CatWithUsed(std::list<std::string>::iterator begin,
                                        std::list<std::string>::iterator end) const;
  std::map<std::string_view, std::pair<std::vector<std::string_view>, std::string_view>> macro_map_{};
  static bool IsNormal(char c);
  static bool IsStringNormal(const std::string& str);
  std::list<std::string> all_macro_{};
};
inline MacroSolver& macro_solver = MacroSolver::GetInstance();
}  // namespace lhy
#endif  // SOLVE_MACRO_H
