# 42sh 🐧

42sh, an Epitech project, the challenge is to recreate a terminal environment similar to tcsh, with a command prompt and features, offering practical experience in shell programming.

## How to run
```bash
make
./42sh
```
## How to run Unit Tests
```bash
make
make test
```
if you want display unit tests:
```bash
cat tests/test
```

## Available Features


| Feature                    | Description                                                                           |
|---------------------------|---------------------------------------------------------------------------------------|
| Bash Command Execution    | Execution of Bash commands within the shell environment                                |
| Built-in Commands         | Implementation of built-in shell commands                                               |
| Redirection               | Input/output redirection using `>` and `>>` for writing to and appending to files, and `<` and `<<` for reading from files |
| Pipelines                 | Ability to chain commands using the pipe operator `\|`                                   |
| Command Sequencing        | Sequential execution of commands separated by `;`                                       |
| Inhibitors                | Usage of inhibitors to control command execution (`\`, `"`, `'`)                        |
| Globbing                  | Pattern matching for file names using `*`, `?`, and `[]`                                |
| Logical Operators         | Support for logical operators `&&` (AND) and `\|\|` (OR) for command execution control    |
| Local and Environment Variables | Management of local and environment variables                                           |
| History                   | Tracking and access to command history                                                   |
| Alias                     | Creation and use of command aliases for convenience                                     |
| Line Edition              | Line editing capabilities for command input using arrow keys and editing shortcuts       |
| Auto-Completion           | Automatic suggestion of commands and file names during command input                     |


## Available Builtins

| Builtin                    | Description                                                                           |
|---------------------------|---------------------------------------------------------------------------------------|
| cd                        | Change the current directory                                                          |
| env                       | Display or modify the environment variables                                             |
| unsetenv                  | Unset one or more environment variables                                                 |
| exit                      | Exit the shell with an optional exit status                                             |
| alias                     | Create or display aliases for commands                                                  |
| unalias                   | Remove aliases for commands                                                            |
| set                       | Set or unset shell options and positional parameters                                     |
| unset                     | Unset values and attributes of shell variables and functions                             |
| history                   | Display command history or manipulate it                                                |
| which                     | Display the full path of shell commands                                                 |
| where                     | Display all locations of a given executable                                              |
| repeat                    | Repeat a command a specified number of times

## Implementation Details

### Lexer and Parser

The system we used in our 42sh relies on a lexer and a parser to analyze the user input and understand its structure. Here is an overview of how it works:

- **Lexer**: The lexer processes the user input by breaking it down into a token, which represents several parts of the command, for example, it identifies keywords such as builtins or separators such as `;`
  
- **Parser**: The parser takes these tokens as input and interprets them against well-defined rules to be able to execute them in the right way

### Token Usage

We use tokens in our implementation to represent different elements of user input. Examples include:

- **Command Tokens**: Represent the main command and its arguments.
- **Operator Tokens**: Represent operators such as redirection (`>`, `<`) and pipes (`|`).

### Example Usage

To show you how the parser lexer works here is an example :

1. `COMMAND`: `ls`
2. `ARGUMENT`: `-l`
3. `PIPE`: `|`
4. `COMMAND`: `grep`
5. `ARGUMENT`: `"example"`

The parser will use these tokens to be able to apply shell rules and execute them.

## Acknowledgements

We would like to thank all the team members for their hard work and determination, thank you for everything:

- [Nicolas Dumetz](https://github.com/NicoDumetz)
- [Maximilien Dheripre](mailto:maximilien.dheripre@gmail.com)
- [Matisse Dufour](mailto:matisse.dufour@outlook.fr)
- [Charles Ignoux](mailto:charles.ignoux@outlook.fr)
- [Charles Faudou](mailto:charles.faudou@outlook.fr)

## Contact

For any questions, suggestions, or feedback, feel free to contact us.
