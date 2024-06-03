/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-matisse.dufour
** File description:
** token_to_str_array.c
*/

#include "minishell.h"

int get_token_list_size(token_t *token)
{
    int i = 0;

    if (!token)
        return i;
    for (; token; token = token->next)
        i++;
    return i;
}

char **token_to_str_array(token_t *start, int end)
{
    char **arr = gmalloc(sizeof(char *) * (end - start->index + 1));
    int i = 0;

    for (token_t *current = start;
        current && current->index <= end;
        current = current->next) {
        if (current->arg) {
            arr[i] = my_gstrdup(current->arg);
            i++;
        }
        if (current->sep == '=') {
            arr[i] = my_gstrdup("=");
            i++;
        }
    }
    arr[i] = NULL;
    return (arr);
}
