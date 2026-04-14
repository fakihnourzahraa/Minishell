# 🐚 Minishell — As beautiful as a shell

> *This project is about creating a simple shell. Yes, your very own little Bash.*
> *You will gain extensive knowledge about processes and file descriptors.*

---

## 📖 About

**Minishell** is a 42 School project that challenges you to implement a functional Unix shell from scratch in C. Inspired by `bash`, it covers command parsing, execution, pipes, redirections, environment variables, signals, and built-in commands — giving you a deep understanding of how a real shell works under the hood.

---

## ✨ Features

### Core Shell Behavior

- Displays a **prompt** when waiting for a new command
- Maintains a working **command history**
- Searches and launches executables using `PATH`, or relative/absolute paths
- Uses a single global variable only to store a received signal number

### Quote Handling

- `'single quotes'` — prevents interpretation of all metacharacters
- `"double quotes"` — prevents interpretation of metacharacters except `$`

### Redirections

| Operator | Description |
|----------|-------------|
| `<`  | Redirect input |
| `>`  | Redirect output |
| `>>` | Redirect output in append mode |
| `<<` | Heredoc — read input until delimiter is found |

### Pipes

- `|` connects the output of one command to the input of the next

### Variable Expansion

- `$VAR` — expands to the value of the environment variable
- `$?` — expands to the exit status of the most recently executed foreground pipeline

### Signals

| Signal | Interactive Behavior |
|--------|----------------------|
| `ctrl-C` | Displays a new prompt on a new line |
| `ctrl-D` | Exits the shell |
| `ctrl-\` | Does nothing |

### Built-in Commands

| Command | Description |
|---------|-------------|
| `echo` | Print text, supports `-n` flag |
| `cd` | Change directory (relative or absolute path) |
| `pwd` | Print current working directory |
| `export` | Set environment variables |
| `unset` | Unset environment variables |
| `env` | Print all environment variables |
| `exit` | Exit the shell |

### Bonus

- `&&` and `||` with parenthesis for priorities
- Wildcards `*` for the current working directory

---

## 🗂 Project Structure

```
minishell/
├── main/               # Entry point, main loop, signal handling, input processing
├── tokenization/       # Lexer: tokenizes raw input into token linked list
├── expansion/          # Variable expansion, quote removal, argument splitting
├── exec/               # Execution engine: single commands, pipelines, redirections, heredoc
├── builtins/           # Built-in command implementations (echo, cd, pwd, export, unset, env, exit)
├── env/                # Environment variable management
├── libft/              # Custom C library (libft)
├── struct.h            # All shared data structures (t_shell, t_cmd, t_token, t_redir, t_env)
└── minishell.h         # Master header
```

---

## 🔧 How to Build

```bash
git clone <repo-url> minishell
cd minishell
make
```

### Run

```bash
./minishell
```

### Clean

```bash
make clean    # Remove object files
make fclean   # Remove object files and binary
make re       # Rebuild everything
```

---

## 📋 Requirements

- Written in **C** following the **42 Norm**
- No unexpected crashes (no segfaults, bus errors, double frees)
- No memory leaks (except those caused by `readline()` itself, which are tolerated)
- Makefile includes: `$(NAME)`, `all`, `clean`, `fclean`, `re`
- Compiled with: `cc -Wall -Wextra -Werror`

---

## 👥 Work Division

| Collaborator | Responsibility |
|---|---|
| **miwehbe** | Execution — pipelines, redirections, heredoc, built-ins, environment, process management (`exec/`, `builtins/`, `env/`) |
| **nfakih** | Parsing — tokenization, quote handling, variable expansion, command structure building (`tokenization/`, `expansion/`, `struct.h`) |

---

*Made with lots of coffee and debugging at 42 Beirut*
