# 42sh 🐧

42sh, a project at Epitech, challenges students to recreate a terminal environment akin to tcsh, complete with a command prompt and functionalities, offering a hands-on experience in shell programming.

## How to run
```bash
make
./42sh
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

Our implementation of 42sh relies on a lexer and parser to analyze the user input and understand its structure. Here's a brief overview of how they work:

- **Lexer**: The lexer processes the input text and breaks it down into tokens, which represent the smallest units of meaning in the command. For example, it identifies keywords, arguments, operators, and punctuation.
  
- **Parser**: The parser takes these tokens as input and constructs a syntax tree, which represents the hierarchical structure of the command. It uses predefined grammar rules to determine how the tokens should be combined to form valid commands.

### Token Usage

We use tokens extensively throughout our implementation to represent different elements of the command syntax. Here are some examples of how tokens are used:

- **Command Tokens**: Represent the main command and its arguments.
- **Operator Tokens**: Represent operators such as redirection (`>`, `<`) and pipes (`|`).

### Example Usage

To demonstrate how our lexer/parser and tokens work in practice, consider the following example:

In this command, the lexer would tokenize it into the following tokens:

1. `COMMAND`: `ls`
2. `ARGUMENT`: `-l`
3. `PIPE`: `|`
4. `COMMAND`: `grep`
5. `ARGUMENT`: `"example"`

The parser would then use these tokens to construct a syntax tree representing the command structure.

## Acknowledgements

We would like to express our sincere gratitude to all members of our group for their hard work, collaboration, and dedication throughout the development of this project. A big thank you to:

- [Nicolas Dumetz](https://github.com/NicoDumetz)
- [Maximilien Dheripre](mailto:maximilien.dheripre@gmail.com)
- [Matisse Dufour](mailto:matisse.dufour@outlook.fr)
- [Charles Ignoux](mailto:charles.ignoux@outlook.fr)
- [Charles Faudou](mailto:charles.faudou@outlook.fr)


Your contributions and support have been instrumental in making this project possible. We are grateful to be working with such a talented and dedicated team.

## Contact

For any questions, suggestions, or feedback, feel free to contact us.
