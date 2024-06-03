/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-matisse.dufour
** File description:
** execute_command.c
*/

#include "my.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

void execute_command(garbage_t *garbage, token_t **token_list, int index)
{
    char **command = token_to_str_array(*token_list, index);

    for (int i = 0; command[i]; i++)
        printf("arg:%s\n", command[i]);
}
