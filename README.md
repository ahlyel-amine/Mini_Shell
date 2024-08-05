# minishell
## Overview
The Minishell project is designed to master process management, command execution, and handling signals in C. It requires understanding of Unix/Linux system calls, particularly those related to process creation, communication between processes (pipes), and signal handling. It implements redirections and pipes, as well as environment variable expansions and the `cd`, `echo`, `env`, `exit`, `export`, `pwd` and `unset` builtin commands.

## Installation

1. Install the dependencies

```bash
  sudo apt update && sudo apt install make git gcc lib32readline8 lib32readline-dev
```

2. Clone the repository

```bash
  git clone git@github.com:ahlyel-amine/Mini_Shell.git && cd Mini_Shell
```

3. To compile Run `make`

* If you have docker simply run `docker compose run --rm minibash`

## Usage

To compile:

```shell
make
```

To run the program:

```shell
./minishell
```

##### **Using docker container**
you can simply run if you have docker installed
```bash
  docker compose run --rm minishell
```

A prompt will appear. You may enter your commands to be executed.

## Supported Features

Minishell is a miniature shell program based on Bash. It supports the following features:

- **Prompt Display**: Minishell displays a prompt indicating readiness for user input.
- **Command History**: Users can navigate command history using the up and down arrow keys.
- **System Executables**: System executables available from the environment (e.g., ls, cat, grep).
- **Local Executables**: Ability to execute local executables using relative or absolute paths (e.g., ./minishell).
- **Builtin Commands**:
  - `echo` with option `-n`.
  - `cd` with only a relative or absolute path.
  - `pwd` with no options.
  - `export` with no options.
  - `unset` with no options.
  - `env` with no options or arguments.
  - `exit` with exit number but no other options.
- **AND and OR Operators**: Support for `&&` and `||` operators with priority using `()` parentheses.
- **Wildcards**: Use of `*` as wildcards.
- **Pipes**: Redirect output from one command to input for the next using the `|` operator.
- **Redirections**:
  - `>`: Redirects output.
  - `>>`: Redirects output in append mode.
  - `<`: Redirects input.
  - `<< DELIMITER`: Displays a new prompt, reads user input until reaching DELIMITER, redirects user input to command input (does not update history).
- **Subshell**: Support for subshells using `()` parentheses.
- **Environment Variables**: Expansion of environment variables (e.g., $USER or $VAR) to their values.
- **$? Expansion**: Expands to the exit status of the most recently executed foreground pipeline.
- **User Keyboard Signals**:
  - `ctrl-c`: Displays a new prompt line.
  - `ctrl-d`: Exits Minishell.
  - `ctrl-\`: Does nothing.

## Unsupported Features

Minishell does not support the following:

- **\ (Backslash)**: Not supported for escaping characters.
- **; (Semicolon)**: Not supported as a command separator.

Please note that Minishell aims to provide a lightweight shell experience with essential functionalities. If you have any questions or suggestions, feel free to reach out!

## Key Concepts and Skills

This project has given you a deep understanding of how a shell works and has helped you develop your skills in various areas:

1. **Process Management**: Creating new processes using `fork()`, and executing commands using `execve()`.
2. **File Descriptors and Redirection**: Manipulating file descriptors to implement redirection (`>`, `>>`, `<`, `<< DELIMITER`) using system calls like `dup2()` and `pipe()`.
3. **Signal Handling**: Handling signals like `SIGINT` (Ctrl-C), `SIGQUIT` (Ctrl-\), and `EOF` (Ctrl-D) using `signal()` or `sigaction()`.
4. **String Manipulation**: Parsing command line input, handling special characters like `*` (wildcards), and expanding environment variables (`$VAR`) and the special variable `$?`.
5. **Builtin Commands**: Implementing builtin commands (`echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`) using system calls and other functions.
6. **Heredoc Redirection (`<< DELIMITER`)**: Reading user input until a specific delimiter is reached and redirecting it to command input.
7. **Execution Tree for Logical Operators (`&&`, `||`) and Subshells (`()`)**: Parsing the command line input into an execution tree to handle logical operators and subshells correctly, likely involving recursive parsing and execution.
## Implementation

### Parsing
Parsing is a critical component of the Minishell project. It involves analyzing the user's input to identify individual commands, arguments, and operators (like redirection symbols). The `parse` function processes the input line, tokenizes it, and prepares it for execution.

### Tokenization
Tokenization is a sub-component of parsing. It breaks down the input string into meaningful tokens, such as commands, arguments, and operators. The `Tokenization` plays a crucial role in this process, identifying and categorizing tokens based on their content and position in the input string.

### Execution
After parsing and tokenization, the Minishell needs to execute the identified commands. This involves creating new processes for each command, managing input/output redirection, and handling signals for graceful termination.

### Error Handling and Cleanup
Proper error handling and resource cleanup are essential for a robust shell application. The Minishell project includes mechanisms to catch and report errors, ensure that resources are freed appropriately, and maintain the integrity of the shell environment.
### Additional Features
- Environment Variables Management: The shell maintains and manipulates environment variables, allowing users to customize their shell experience.
- Signal Handling: The Minishell implements signal handling to allow users to interrupt and terminate processes gracefully.
- Process Management: The shell creates and manages child processes for executing commands, demonstrating the principles of process synchronization and communication.
## Challenges
- Implementing signal handling for interrupting and terminating processes gracefully.
- Supporting job control features like foreground and background jobs.
- Enhancing the shell with scripting capabilities.

<h1>Final Mark</h1>

![Alt text](final_mark.png?raw=true "Final Mark")
