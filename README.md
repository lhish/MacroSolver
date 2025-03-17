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

## 为什么不通过编译器源码来学习宏 / Why not learn macros by studying the compiler source code?

C/C++ 宏机制的底层实现细节通常隐藏在复杂的编译器源码中。理解编译器源码本身极具挑战性，需要深入掌握编译原理和底层架构。*
*编译器源码晦涩难懂，即使是经验丰富的开发者也常常望而却步。**

**相对于直接研究编译器源码，MacroSolver 提供了一个更易于理解和学习的替代方案。**  它通过简洁的代码和清晰的逻辑，展示了宏展开的核心原理。你可以通过阅读、调试和修改
MacroSolver 的代码，更直观地理解宏展开的过程，而无需深入研究庞大而复杂的编译器源码。

This project provides a more accessible alternative to directly diving into the intricate details of compiler source
code. The underlying implementation of C/C++ macro mechanisms is often concealed within the complex compiler source.
Understanding compiler source code is inherently challenging, requiring a deep grasp of compilation principles and
underlying architecture. **Compiler source code can be notoriously dense and difficult to understand, often intimidating
even experienced developers.**

**MacroSolver offers a more understandable and approachable way to learn. Instead of struggling with the complexity of
compiler code,** It demonstrates the core principles of macro expansion through concise code and clear logic. By
reading, debugging, and modifying MacroSolver's code, you can gain a more intuitive understanding of the macro expansion
process without the need to delve into vast and complex compiler source code

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