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
	  src/lexer_parser/lexing.c\
	  src/cd.c \
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
	  src/globbings/globbings.c\
	  src/globbings/assemble_simple.c\
	  src/globbings/assemble_hard.c\
	  tools/tab_len.c\
	  tools/token_to_str_array.c\
	  tools/free_token.c
	  tools/token_to_str.c\
	  src/alias/alias.c \
	  src/local/local_var.c \
	  tools/clean_str.c \
	  src/globs_tab.c \
	  tools/contain_char.c \
	  src/builtins_tab.c \
	  tools/array_to_str.c \
	  src/execution_functions/execute_built.c \

OBJ = $(SRC:.c=.o)

CFLAGS += -Llib -lmy -Iinclude -g

NAME = 42sh

all: $(NAME)

required:
	@./tests/banner.sh
	@printf "\e[1;32m"
	@make -s -C lib/my

$(NAME): required $(OBJ)
	@gcc -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	printf "\e[36m"
	rm -f $(OBJ)
	make -s clean -C lib/my

fclean:
	@printf "\e[35m"
	rm -f $(NAME)
	rm -f $(OBJ)
	make fclean -s -C lib/my

re: fclean all

run_test:
	@./tests/tester.sh
