##
## EPITECH PROJECT, 2024
## B-PSU-200-LIL-2-1-minishell1-matisse.dufour
## File description:
## Makefile
##

SRC = main.c \
	  src/lexer_parser/lexer/lexing.c\
	  src/lexer_parser/lexer/lexing_features.c\
	  src/feature_tab.c\
	  src/globbings/globbings.c\
	  src/cd.c \
	  src/exit_built.c\
	  src/env.c \
	  src/setenv.c \
	  src/new_process.c \
	  src/execution_functions/init_pipeline.c \
	  src/execution_functions/process_execution.c \
	  src/execution_functions/pipe/pipe.c \
	  src/execution_functions/pipe/fork.c \
	  src/execution_functions/redirection/redirection.c \
	  src/execution_functions/redirection/redirection_errors.c \
	  src/execution_functions/conditionnal_execution.c \
	  src/command_errors.c\
	  src/add_separator.c\
	  tools/tab_len.c\
	  tools/token_to_str_array.c\
	  tools/token_to_str.c\
	  src/alias/alias.c \
	  src/local/local_var.c \
	  tools/clean_str.c \
	  src/globs_tab.c \
	  tools/contain_char.c \
	  src/builtins_tab.c \
	  tools/array_to_str.c \
	  src/execution_functions/execute_built.c \
	  tools/free_array.c \
	  tools/free_token.c \
	  src/var_env/var_env.c \
	  src/local/manage_local.c \
	  src/alias/manage_alias.c \
	  src/history/add_history.c \
	  src/history/display_history.c \
	  src/history/history_command.c \
	  src/history/history_arrows.c \
	  src/history/my_str_to_minishell_array.c \
	  src/history/my_str_to_minishell_array2.c \
	  src/history/my_str_to_minishell_array3.c \
	  src/input_management/input_management.c \
	  src/input_management/my_getline.c \
	  src/input_management/non_canonical_mode.c \
	  src/input_management/command_management.c \
	  src/globbings/assemble_hard.c \
	  src/globbings/assemble_simple.c \
	  src/cleanup.c \

OBJ = $(SRC:.c=.o)

CFLAGS += -Llib -lmy -Iinclude -g

NAME = 42sh

all: $(NAME)

required:
	make -C lib/my

$(NAME): required $(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)
	make clean -C lib/my

fclean:
	rm -f $(NAME)
	rm -f $(OBJ)
	make fclean -C lib/my

re: fclean all
