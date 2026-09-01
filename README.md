# Mini Compiler in C

A simplified end-to-end compiler implemented completely in C for the Compiler Design project.

## Features

- Lexical Analysis
- Syntax Analysis using Recursive Descent Parsing
- Semantic Analysis
- Symbol Table Management
- Three Address Code (TAC) Generation
- Basic Code Optimization
- Assembly-like Target Code Generation

## Supported Language Features

- Integer declarations
- Variable assignments
- Integer constants
- Arithmetic operators: `+`, `-`, `*`, `/`
- Parentheses

Example:

```c
int a;
int b;
int c;

a = 10;
b = 20;
c = a + b * 2;
```

## Compiler Architecture

```text
Source Code
    |
    v
Lexical Analyzer
    |
    v
Tokens
    |
    v
Parser
    |
    v
Semantic Analysis
    |
    v
Three Address Code
    |
    v
Code Optimization
    |
    v
Target Code Generation
```

## Project Files

- `compiler.h` - Common header file and shared definitions
- `lexer.c` - Lexical analyzer
- `parser.c` - Syntax analysis and parsing
- `semantic.c` - Symbol table and semantic checks
- `tac.c` - Three Address Code generation
- `optimizer.c` - Basic code optimization
- `target_codegen.c` - Assembly-like target code generation
- `main.c` - Main driver program

## Compilation

Compile all files using GCC:

```bash
gcc main.c lexer.c parser.c semantic.c tac.c optimizer.c target_codegen.c -o compiler
```

## Run

```bash
./compiler
```

## Semantic Checks

The compiler currently detects:

- Use of undeclared variables
- Duplicate variable declarations

## Example TAC

Input:

```c
c = a + b * 2;
```

Output:

```text
t1 = b * 2
t2 = a + t1
c = t2
```

## Optimization

Implemented optimizations include:

- Constant Folding
- Algebraic Simplification

Examples:

```text
5 * 2  -> 10
a + 0  -> a
a * 1  -> a
a * 0  -> 0
```

## Team

The project is divided into three major responsibilities:

1. Lexical Analysis and Syntax Analysis and Integration
2. Semantic Analysis and Intermediate Code Generation
3. Code Optimization, Target Code Generation
