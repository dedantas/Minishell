# Minishell

A fully functional **Unix shell** built in **C**, designed to mimic the behavior of **Bash** while reinforcing knowledge of process management, pipes, signals, and parsing.
It provides a complete interactive shell experience with built-in commands, environment handling, and robust execution flow.

## Features

- **Interactive prompt** for executing commands  
- **Built-in commands**: `cd`, `echo`, `env`, `exit`, `export`, `pwd`, `unset`  
- **Pipes** (`|`) and **redirections** (`<`, `>`, `>>`, `<<`)  
- **Environment variable expansion** (e.g. `$USER`, `$PATH`)  
- **Signal handling** for `Ctrl + C`, `Ctrl + D`, and `Ctrl + \`  
- **Error messages** consistent with Bash  
- **Memory-safe execution** (no leaks, fully cleaned after exit)  

## Tech Stack

- **C** – Core language  
- **GNU Readline** – For interactive input
- **POSIX system calls** – `fork`, `execvp`, `pipe`, `dup2`, `wait`, `signal`, etc.  
- **Makefile** – For easy build and management

## Installation

1. Clone the repository:

```bash
git clone https://github.com/dedantas/Minishell
cd Minishell
```

2. Compile the project:

```bash
make
```

3. Run the executable:

```bash
./minishell
```

## Usage

- **Run commands** just like in Bash:

```bash
minishell$ ls -l | grep minishell
```

- **Set and use environment variables:**

```bash
minishell$ export NAME= <name>
minishell$ echo "Hello $NAME"
Hello <name>
```

- **Redirect input and output:**

```bash
minishell$ cat < input.txt | grep "data" > output.txt
```

- **Exit the shell:**

```bash
minishell$ exit
```

## Compilation

- Build the executable:

```bash
make
```

- Remove object files:

```bash
make clean
```

- Remove all binaries and rebuild:

```bash
make re
```

## License

Educational project under 42 School academic policy.
