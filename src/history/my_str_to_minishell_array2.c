/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell2-charles.ignoux
** File description:
** my_str_to_error_handling2.c
*/

#include <stdlib.h>

int my_c_redi_pipe(char c)
{
    if (c == '<' || c == '>' || c == '|' || c == '&')
        return 1;
    return 0;
}

int my_c_pipe(char c)
{
    if (c == '|')
        return 1;
    return 0;
}

int my_c_esp(char c)
{
    if (c == '&')
        return 1;
    return 0;
}

void add_pipe(char **tab, int **index, char const *str, int *h)
{
    int counter;

    for (counter = 0; str[*h] != '\0' && counter < 2
        && my_c_pipe(str[*h]) == 1; counter++)
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

void add_esp(char **tab, int **index, char const *str, int *h)
{
    int counter;

    for (counter = 0; str[*h] != '\0' && counter < 2
        && my_c_esp(str[*h]) == 1; counter++)
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
