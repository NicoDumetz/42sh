/*
** EPITECH PROJECT, 2024
** MiniShell
** File description:
** check_command.c
*/

#include "../include/minishell.h"

void manage_double(char *str, char *new_str, int *index, int *i)
{
    if (str[*i] != ';' && str[*i] != ")" && str[*i] != "(" &&
        str[*i + 1] != '\0' && (str[*i] == str[*i + 1])) {
        (*index)++;
        new_str[*index] = str[*i + 1];
        *i = *i + 1;
    }
}

void add_space(char *new_str, char *str, int *index, int *i)
{
    if (*index != 0 && new_str[*index - 1] != ' ') {
        new_str[*index] = ' ';
        (*index)++;
    }
    new_str[*index] = str[*i];
    manage_double(str, new_str, index, i);
    (*index)++;
    new_str[*index] = ' ';
    (*index)++;
}

void insert_spaces(char **input)
{
    char *str = *input;
    char *tmp;
    char new_str[2 * my_strlen(*input)];
    int index = 0;
    int j = 0;
    char *items = "><|;)(&";

    for (int i = 0; str[i]; i++) {
        for (j = 0; items[j] != str[i] && items[j]; j++);
        if (j < my_strlen(items)) {
            add_space(new_str, str, &index, &i);
        } else {
            new_str[index] = str[i];
            index++;
        }
    }
    new_str[index] = '\0';
    tmp = my_strdup(new_str);
    free(*input);
    *input = tmp;
}
