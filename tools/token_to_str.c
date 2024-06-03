/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-matisse.dufour
** File description:
** token_to_str.c
*/

#include "minishell.h"

char *token_to_str(token_t *start, int end)
{
    char *str = malloc_str(0);
    int i = 0;

    for (token_t *current = start;
        current && current->index <= end;
        current = current->next) {
        if (current->sep)
            i++;
        if (current->arg)
            i += strlen(current->arg);
    }
    return str;
}