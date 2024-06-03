/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-matisse.dufour
** File description:
** parsing.c
*/

#include "my.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

static int process_separator(token_t *token, garbage_t *garbage, token_t **token_list)
{
    int i = 0;

    for (i = 0; r_tab[i].sep != 0 && token->sep != r_tab[i].sep; i++);
    if (r_tab[i].sep == 0)
        return EXIT_FAILURE;
    r_tab[i].redirection(garbage, token_list);
    return EXIT_SUCCESS;
}

int parsing_function(garbage_t *garbage, token_t **token_list)
{
    token_t *token = *token_list;
    int index = 0;

    if (!token)
        return -1;
    for (; token; token = token->next) {
        if (token->sep && token->sep != ' ' && token->sep != '\n') {
            return process_separator(token, garbage, token_list);
        }
        index = token->index;
    }
    garbage->return_value = new_process(token_to_str_array(*token_list, index),
                *(garbage->env));
    return EXIT_SUCCESS;
}
