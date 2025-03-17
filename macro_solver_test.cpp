//
// Created by lhy on 25-3-12.
//
#include <fstream>
#include <iostream>

#include "solve_macro.h"
using namespace lhy;
int main() {
  for (int i = 1; i <= 9; i++) {
    std::ifstream file(std::string("../define_list") + std::to_string(i) + ".txt");
    std::string line;
    std::string final_line;
    while (std::getline(file, line)) {
      if (line[0] == '#' || final_line != "") {
        final_line += line.substr(0, line.size());
        if (line.substr(line.size() - 1, 1) != "\\") {
          macro_solver.AddMacro(final_line);
          final_line = "";
        } else {
          final_line.pop_back();
        }
      } else {
        std::cout << macro_solver.SolveOneMacro(line) << std::endl;
        std::cout << std::endl;
      }
    }
    macro_solver.ClearAllMacro();
  }
}