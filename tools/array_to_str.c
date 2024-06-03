/*
** EPITECH PROJECT, 2024
** array_to_str
** File description:
** array_to_str
*/

#include "minishell.h"

static int array_len(char **array)
{
    int compt;

    for (compt = 0; array[compt]; compt++);
    return compt;
}

static void concat_space(char *str, int *index)
{
    my_strcat(str, " ");
    *index += 1;
}

char *array_to_str(char **array)
{
    int num = array_len(array);
    int len = 0;
    char *str;
    int index = 0;

    for (int i = 0; i < num; i++)
        len += strlen(array[i]);
    len += num - 1;
    str = (char *)gmalloc(len + 1);
    str[0] = '\0';
    for (int i = 0; i < num; i++) {
        my_strcat(str, array[i]);
        index += strlen(array[i]);
        if (i < num - 1 && array[i + 1] && strcmp(array[i + 1], "=")
            != 0 && strcmp(array[i], "=") != 0)
            concat_space(str, &index);
    }
    str[index] = '\0';
    return str;
}
