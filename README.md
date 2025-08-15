# MacroSolver

MacroSolver 是一个 C++ 宏展开工具，专注于解析和展开 C/C++ 预处理器中的函数式宏定义。本项目是学习和深入理解 C++ 宏机制的绝佳资源。

本项目是全球首个实现跨平台可视化宏扩展的工具，能够清晰地展示宏展开的每一步过程。它全面支持所有函数宏特性，尽管 Visual
Studio 也提供了类似功能，但缺乏跨平台能力。更重要的是，我们的项目在原理上完全公开，透明度极高。

MacroSolver is a C++ macro expansion tool specifically designed for parsing and expanding function-like preprocessor
macros in C/C++. This project stands as an excellent resource for learning and gaining a deep understanding of C++ macro
mechanisms.

MacroSolver is the world's first tool to offer cross-platform visual macro expansion, clearly illustrating each step of
the expansion process. It fully supports all features of function-like macros. While Visual Studio offers similar
functionality, it lacks cross-platform capabilities. Crucially, our project boasts unparalleled transparency due to its
fully disclosed underlying principles.

## 对伪递归的简单演示 / Simple Demonstration of Pseudo-Recursion

**场景描述 (Scenario Description):**

以下宏定义模拟了一种“伪递归”的行为，即一个宏通过列表展开来调用自身（或相似的结构），尽管 C++ 预处理器本身并不直接支持递归。

The following macro definition simulates a form of "pseudo-recursion." A macro calls itself (or similar structures)
through list expansion, even though C++ preprocessor itself does not directly support recursion.

```cpp
#define f(x) void x();
FOREACH(f, a, b, c)
```

**展开结果 / Expanded Result:**

```cpp
void a();

void b();

void c();
```

## 功能特点 / Features

- 支持基本的宏定义和展开
- 支持带参数的宏
- 支持嵌套宏展开
- 支持字符串化操作符 (#)
- 支持标记连接操作符 (##)
- 支持可变参数宏 (__VA_ARGS__)
- 支持__VA_OPT__扩展
- 支持伪递归
- Basic macro definitions and expansions
- Macros with parameters
- Nested macro expansions
- Stringification operator (#)
- Token pasting operator (##)
- Variadic macros (__VA_ARGS__)
- __VA_OPT__ extensions
- Supports pseudo-recursion

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
