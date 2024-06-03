##
## EPITECH PROJECT, 2024
## B-PSU-200-LIL-2-1-minishell1-matisse.dufour
## File description:
## Makefile
##

SRC = main.c \
	  src/lexer_parser/lexer/lexing.c\
	  src/lexer_parser/lexer/lexing_features.c\
	  src/lexer_parser/parser/parsing.c\
	  src/feature_tab.c\
	  src/execute_command.c\
	  src/globbings/globbings.c\
	  src/cd.c \
	  src/env.c \
	  src/setenv.c \
	  src/new_process.c \
	  src/pipe/pipe.c \
	  src/pipe/fork.c \
	  src/redirection/redirection.c \
	  src/redirection/redirection_errors.c \
	  src/command_errors.c\
	  src/add_separator.c\
	  tools/tab_len.c\
	  tools/token_to_str_array.c\
	  src/alias/alias.c

OBJ = $(SRC:.c=.o)

CFLAGS += -Llib -lmy -Iinclude -g

NAME = mysh

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
