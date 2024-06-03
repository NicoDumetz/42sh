/*
** EPITECH PROJECT, 2024
** invalid char
** File description:
** invalid char
*/

#include "minishell.h"

int invalid_char(char *str)
{
    for (int i = 0; str[i]; i++) {
        if (str[i] > 0 && str[i] < 31 && str[i] != 10 && str[i] != 9) {
            return 1;
        }
    }
    return 0;
}
