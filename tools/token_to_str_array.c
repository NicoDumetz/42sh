/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-matisse.dufour
** File description:
** token_to_str_array.c
*/

#include "minishell.h"

char **token_to_str_array(token_t *start, int end)
{
    char **arr = malloc(sizeof(char *) * (end - start->index + 1));
    int i = 0;

    for (token_t *current = start;
        current && current->index <= end;
        current = current->next)
        if (current->arg) {
            arr[i] = strdup(current->arg);
            i++;
        }
    arr[i] = NULL;
    return (arr);
}
