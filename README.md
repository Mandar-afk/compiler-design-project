# Mini Compiler - C + Bison

A small end-to-end compiler implemented in C, using a handwritten C lexer and GNU Bison for LALR parsing.

## Features
- `int` declarations
- Assignments
- Integer constants
- `+`, `-`, `*`, `/`
- Parentheses
- Unary `+` and unary `-`
- Semantic rules: declaration before use and no duplicate declaration
- Identifier length limit: 20 characters
- Three Address Code generation
- Constant folding and basic algebraic simplification
- Simple assembly-like target code

## Architecture
Source -> C Lexer -> Bison LALR Parser -> Semantic Analysis -> TAC -> Optimization -> Target Code

## Files
- `compiler.h` - shared declarations and limits
- `lexer.c` - handwritten C lexical analyzer and Bison token interface
- `parser.y` - Bison grammar and semantic/TAC actions
- `semantic.c` - symbol table and semantic checks
- `tac.c` - Three Address Code
- `optimizer.c` - basic optimization
- `target_codegen.c` - target-code generation
- `main.c` - integration and hardcoded test source
- `test_cases.txt` - test cases
- `Makefile` - build commands

## Install on Fedora
```bash
sudo dnf install gcc bison make
```

Flex is NOT required because the lexer is handwritten in `lexer.c`.

## Compile
Option 1:
```bash
make
```

Option 2:
```bash
bison -d parser.y
gcc -std=c11 -Wall -Wextra -pedantic parser.tab.c lexer.c semantic.c tac.c optimizer.c target_codegen.c main.c -o compiler
```

## Run
```bash
./compiler
```

The current source program is inside `main.c`. Change `sourceCode` and recompile to test another program.

## Important Bison files
`bison -d parser.y` generates:
- `parser.tab.c` - generated LALR parser implementation
- `parser.tab.h` - generated token definitions/header used by the lexer

Do not edit these generated files manually.

## Unary operators
Examples:
```text
+5
-5
-(a + b)
+a * -b
```
Unary `+` is a no-op. Unary `-` is represented internally as `0 - operand` in TAC.

## Identifier length rule
Identifiers can contain letters, digits and `_`, must start with a letter or `_`, and must be at most 20 characters long. Longer identifiers cause a lexical error.

## Semantic rules
1. A variable must be declared before it is used.
2. A variable cannot be declared more than once.
3. Only integer variables are supported.
4. Identifier length cannot exceed 20 characters.

## Suggested demonstration test
Use this in `main.c`:
```c
const char *sourceCode =
    "int a;"
    "int b;"
    "int result;"
    "a = 10;"
    "b = -5;"
    "result = +(a + b * 2) - -3;";
```

Expected key behavior:
- unary `-5` is accepted
- unary `+` is accepted
- `b * 2` is evaluated before `a + ...`
- `- -3` is accepted
- parsing and semantic analysis finish successfully
