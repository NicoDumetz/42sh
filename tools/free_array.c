/*
** EPITECH PROJECT, 2024
** free array
** File description:
** free array
*/

#include "minishell.h"

void free_array(char **arr)
{
    if (arr == NULL)
        return;
    for (int i = 0; arr[i]; i++)
        free(arr[i]);
    free(arr);
}
