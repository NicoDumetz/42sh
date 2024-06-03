/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-matisse.dufour
** File description:
** conditionnal_execution.c
*/

#include "my.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int execute_semicolon(garbage_t *garbage, token_t **token_list, token_t *token)
{
    garbage->return_value = new_process(token_to_str_array(*token_list, token->index), *garbage->env);
    return 0;
}
