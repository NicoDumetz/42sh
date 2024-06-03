##
## EPITECH PROJECT, 2024
## B-PSU-200-LIL-2-1-minishell1-matisse.dufour
## File description:
## Makefile
##

SRC = main.c \
	  src/cd.c \
	  src/env.c \
	  src/setenv.c \
	  src/new_process.c \
	  src/pipe/pipe.c \
	  src/pipe/fork.c \
	  src/redirection/redirection.c \
	  src/redirection/redirection_errors.c \
	  src/command_errors.c\
	  src/add_separator.c

OBJ = $(SRC:.c=.o)

CFLAGS += -Llib -lmy -Iinclude -g

NAME = mysh


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
