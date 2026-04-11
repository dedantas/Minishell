*This project has been created as part of the 42 curriculum by dedantas, vilopes.*

# Minishell

## Description

Minishell is a simplified Unix shell developed as part of the 42 curriculum.  
The goal of this project is to recreate a basic command-line interpreter that mimics the behavior of Bash.

This includes:
- Executing commands with arguments
- Handling environment variables
- Managing input/output redirections
- Supporting pipes
- Implementing built-in commands

The project focuses on understanding process creation, file descriptors, and signal handling in Unix systems.

## Features

- Command execution (absolute, relative, and via PATH)
- Built-in commands:
  - `echo`
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- Pipes (`|`)
- Redirections:
  - Input (`<`)
  - Output (`>`)
  - Append (`>>`)
  - Heredoc (`<<`)
- Environment variable expansion (`$VAR`)
- Signal handling (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`)

## Instructions

### Compilation

Clone the repository and compile using `make`:

```bash
git clone <repository_url>
cd minishell
make

Execution

Run the shell with:

./minishell

Usage Example
Understanding concepts like process management and pipes
Clarifying system call behavior (fork, execve, etc.)
Structuring the parsing logic
Debugging specific edge cases

All implementation decisions and final code were written and validated by the authors.

Authors
dedantas
vilopes
