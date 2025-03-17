# MacroSolver

MacroSolver是一个C++宏展开工具，用于解析和展开C/C++预处理器宏定义，但只支持函数式宏。这个项目是学习和理解C++宏机制的最佳资源之一。

MacroSolver is a C++ macro expansion tool designed for parsing and expanding C/C++ preprocessor macro definitions, but
only supports function-like macros. This
project serves as an excellent learning resource for understanding the intricacies of C++ macros.

## 功能特点 / Features

- 支持基本的宏定义和展开
- 支持带参数的宏
- 支持嵌套宏展开
- 支持字符串化操作符 (#)
- 支持标记连接操作符 (##)
- 支持可变参数宏 (__VA_ARGS__)
- 支持__VA_OPT__扩展
- 防止宏递归展开

- Basic macro definitions and expansions
- Macros with parameters
- Nested macro expansions
- Stringification operator (#)
- Token pasting operator (##)
- Variadic macros (__VA_ARGS__)
- __VA_OPT__ extensions
- Prevention of recursive macro expansions

## 项目结构 / Project Structure

```
├── CMakeLists.txt
├── Doxygen.config
├── LICENSE
├── README.md
├── define_list1.txt - define_list9.txt  // Macro definition files for testing
├── macro_solver_test.cpp                // Test program
└── my_std
    └── normal
        ├── CMakeLists.txt
        ├── include
        │   └── solve_macro.h            // Header file
        └── src
            └── solve_macro.cpp          // Implementation file
```

##        