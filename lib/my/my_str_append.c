/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-matisse.dufour
** File description:
** tab_len.c
*/

#include "my.h"

char *my_str_append(char *dest, char const *src)
{
    char *str = NULL;
    int i = 0;
    int j = 0;

    str = malloc_str(strlen(dest) + strlen(src));
    for (i = 0; dest[i]; i++) {
        str[i] = dest[i];
    }
    j = i;
    for (j = 0; src[j]; j++) {
        str[i] = src[j];
        i++;
    }
    free(dest);
    return str;
}