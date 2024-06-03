/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-matisse.dufour
** File description:
** token_to_str.c
*/

#include "minishell.h"

char *token_to_str(token_t *start)
{
    char *str = malloc_str(0);
    int i = 0;

    for (; start; start = start->next) {
        if (start->sep) {
            str = my_str_append_char(str, start->sep);
        }
        if (start->arg)
            str = my_str_append(str, start->arg);
    }
    return str;
}