/*
** EPITECH PROJECT, 2024
** clean str
** File description:
** clean str
*/

#include "minishell.h"


static void remove_space(char *str)
{
    for (int i = 0; i <= strlen(str); i++)
        str[i] = str[i + 1];
}

void clean_space(char *str)
{
    int k = 0;

    for (int i = 0; str[i]; i++) {
        if (str[i] == '\t')
            str[i] = ' ';
    }
    for (int i = 0; str[i]; i++) {
        if (str[i] == ' ')
            remove_space(str + i);
    }
}
