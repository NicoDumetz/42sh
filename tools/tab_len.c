/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-matisse.dufour
** File description:
** tab_len.c
*/

#include "minishell.h"

int tab_len(char **tab)
{
    int count = 0;

    if (tab != NULL)
        for (; tab[count]; count++)
    return (count);
}
