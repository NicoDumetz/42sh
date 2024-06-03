/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell2-charles.ignoux
** File description:
** my_str_to_minishell_array2.c
*/

#include <stdlib.h>

int my_c_redi_r(char c)
{
    if (c == '>')
        return 1;
    return 0;
}

int my_c_redi_g(char c)
{
    if (c == '<')
        return 1;
    return 0;
}

void add_redi_r(char **tab, int **index, char const *str, int *h)
{
    int counter;

    for (counter = 0; str[*h] != '\0' && counter < 2
        && my_c_redi_r(str[*h]) == 1; counter++)
        (*h)++;
    if (counter != 0) {
        tab[*index[0]] = malloc(counter + 1);
        for (; counter > 0; counter--) {
            tab[*index[0]][*index[1]] = str[*h - counter];
            (*index[1])++;
        }
        tab[*index[0]][*index[1]] = '\0';
        (*index[0])++;
        *index[1] = 0;
    }
}

void add_redi_g(char **tab, int **index, char const *str, int *h)
{
    int counter;

    for (counter = 0; str[*h] != '\0' && counter < 2
        && my_c_redi_g(str[*h]) == 1; counter++)
        (*h)++;
    if (counter != 0) {
        tab[*index[0]] = malloc(counter + 1);
        for (; counter > 0; counter--) {
            tab[*index[0]][*index[1]] = str[*h - counter];
            (*index[1])++;
        }
        tab[*index[0]][*index[1]] = '\0';
        (*index[0])++;
        *index[1] = 0;
    }
}
