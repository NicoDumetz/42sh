/*
** EPITECH PROJECT, 2023
** my_str_to_word_array
** File description:
** qzdsqzd
*/

#include <stdlib.h>

static int my_c_isnt_separateur(char c, char *separateur)
{
    int i;

    for (i = 0; separateur[i] != '\0'; i++) {
        if (c == separateur[i])
            return 0;
    }
    return (1);
}

static void close_word(char **tab, int *j, int *i)
{
    tab[*i][*j] = '\0';
    if (*j != 0)
        (*i)++;
    *j = 0;
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

    while (my_c_isnt_separateur(str[i], separateur) == 1 && str[i] != '\0') {
        i++;
    }
    return (i);
}

static int counter_word(char const *str, char *separateur)
{
    int i = 0;
    int j = 0;
    int h = 0;

    while (str[h] != '\0') {
        while ((my_c_isnt_separateur(str[h], separateur) == 1)
            && str[h] != '\0') {
            h++;
            j++;
        }
        pass_sep(str, &h, separateur);
        if (j != 0)
            (i)++;
        j = 0;
    }
    return (i);
}

static char **fill_array(char **tab, char const *str, char *separateur)
{
    int i = 0;
    int j = 0;
    int h = 0;

    while (str[h] != '\0') {
        tab[i] = malloc(len_word(&str[h], separateur) + 1);
        if (tab[i] == NULL)
            return NULL;
        while (my_c_isnt_separateur(str[h], separateur)
            == 1 && str[h] != '\0') {
            tab[i][j] = str[h];
            h++;
            j++;
        }
        close_word(tab, &j, &i);
        pass_sep(str, &h, separateur);
    }
    tab[i] = 0;
    return (tab);
}

char **my_str_to_word_array_char(char const *str, char *separateur)
{
    char **tab;

    tab = malloc(sizeof(char *) * (counter_word(str, separateur) + 1));
    if (tab == NULL)
        return NULL;
    return fill_array(tab, str, separateur);
}
