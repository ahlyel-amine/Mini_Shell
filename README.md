# minishell



Minishell is a 42 school team project to create a basic shell program in C. It implements redirections and pipes, as well as environment variable expansions and the `cd`, `echo`, `env`, `exit`, `export`, `pwd` and `unset` builtin commands.


## Usage


To compile:

```shell
make
```

To run the program:

```shell
./minishell
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
