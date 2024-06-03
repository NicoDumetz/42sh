/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell2-charles.ignoux
** File description:
** my_str_to_error_handling.c
*/

#include <stdlib.h>
#include "minishell.h"

static int my_c_isnt_separateur(char c, char *separateur)
{
    int i;

    for (i = 0; separateur[i] != '\0'; i++) {
        if (c == separateur[i])
            return 0;
    }
    return (1);
}

static void close_open_word(char **tab, int **index, char const *str, int *h)
{
    tab[*index[0]][*index[1]] = '\0';
    if (*index[1] != 0)
        (*index[0])++;
    *index[1] = 0;
    add_pipe(tab, index, str, h);
    add_redi_r(tab, index, str, h);
    add_redi_g(tab, index, str, h);
}

static void check_redi(char const *str, int *h, int *i)
{
    int counter;

    for (counter = 0; str[*h] != '\0' && counter < 2
        && my_c_pipe(str[*h]) == 1; counter++)
        (*h)++;
    if (counter != 0)
        (*i)++;
    for (counter = 0; str[*h] != '\0' && counter < 2
        && my_c_redi_r(str[*h]) == 1; counter++)
        (*h)++;
    if (counter != 0)
        (*i)++;
    for (counter = 0; str[*h] != '\0' && counter < 2
        && my_c_redi_g(str[*h]) == 1; counter++)
        (*h)++;
    if (counter != 0)
        (*i)++;
}

static void pass_sep(char const *str, int *h, char *separateur)
{
    while (my_c_isnt_separateur(str[*h], separateur) == 0 && str[*h] != '\0') {
        (*h)++;
    }
}

static int len_word(char const *str, char *separateur)
{
    int i = 0;

    while (my_c_isnt_separateur(str[i], separateur) == 1 && my_c_redi_pipe
    (str[i]) != 1 && str[i] != '\0')
        i++;
    if (i != 0)
        return i;
    for (i = 0; str[i] != '\0' && i < 2 && my_c_pipe(str[i]) == 1; i++);
    if (i != 0)
        return i;
    for (i = 0; str[i] != '\0' && i < 2 && my_c_redi_r(str[i]) == 1; i++);
    if (i != 0)
        return i;
    for (i = 0; str[i] != '\0' && i < 2 && my_c_redi_g(str[i]) == 1; i++);
    return i;
}

static int counter_word(char const *str, char *separateur)
{
    int i = 0;
    int j = 0;
    int h = 0;

    while (str[h] != '\0') {
        while (my_c_isnt_separateur(str[h], separateur) == 1 &&
            my_c_redi_pipe(str[h]) != 1 && str[h] != '\0') {
            h++;
            j++;
        }
        pass_sep(str, &h, separateur);
        check_redi(str, &h, &i);
        if (j != 0)
            (i)++;
        j = 0;
    }
    return (i);
}

char **my_str_to_minishell_array(char const *str, char *separateur)
{
    int i = 0;
    int j = 0;
    int h = 0;
    char **tab;

    tab = malloc(sizeof(char *) * (counter_word(str, separateur) + 1));
    while (str[h] != '\0') {
        tab[i] = malloc(len_word(&str[h], separateur) + 1);
        while (str[h] != '\0' && my_c_isnt_separateur(str[h], separateur) == 1
            && my_c_redi_pipe(str[h]) != 1) {
            tab[i][j] = str[h];
            h++;
            j++;
        }
        close_open_word(tab, (int *[2]){&i, &j}, str, &h);
        pass_sep(str, &h, separateur);
    }
    tab[i] = 0;
    return (tab);
}
