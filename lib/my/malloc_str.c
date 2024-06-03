/*
** EPITECH PROJECT, 2023
** malloc_array.c
** File description:
** malloc a string
*/

#include "my.h"
#include "../../include/minishell.h"

char *malloc_str(int size)
{
    char *str = gmalloc(sizeof(char) * (size + 1));

    if (!str)
        return NULL;
    for (int i = 0; i <= size; i++)
        str[i] = '\0';
    return str;
}
