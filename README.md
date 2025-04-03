# Expression Evaluator in C

This project is a simple expression evaluator implemented in C. It reads infix arithmetic expressions from a file, converts them to postfix (Reverse Polish Notation), builds an expression tree, and evaluates the result using tree traversal.

## 💡 Features

- Reads arithmetic expressions from `input.txt`.
- Converts infix expressions to postfix notation manually.
- Builds an expression tree from postfix expressions.
- Evaluates the final result using post-order traversal.
- Prints original infix, postfix expression, and result.
- Saves results to `output.txt`.

## 🧠 Supported Expression Elements

The code supports:
- **Binary operators**: `+`, `-`, `*`, `/`, `%`
- **Integer numbers only**
- **Parentheses** for controlling precedence, e.g., `(1+2)*3`

## ❌ Limitations

- ❌ **No support for negative numbers** (e.g., `-5 + 3` is not handled correctly).
- ❌ **No support for floating-point numbers** (e.g., `3.14`).

## 🗂️ File Structure

- `main.c`: Contains all the source code.
- `input.txt`: Input expressions, one per line.
- `output.txt`: Generated automatically with postfix expressions and their evaluation.
