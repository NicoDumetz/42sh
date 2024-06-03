/*
** EPITECH PROJECT, 2024
** contain char
** File description:
** contain char
*/

#include "minishell.h"

int contain(char *str, char character)
{
    for (int i = 0; str[i]; i++) {
        if (str[i] == character)
            return 1;
    }
    return 0;
}
