/*
** EPITECH PROJECT, 2024
** free array
** File description:
** free array
*/

#include "minishell.h"

int free_array(char **arr)
{
    if (arr == NULL)
        return 0;
    for (int i = 0; arr[i]; i++)
        free(arr[i]);
    free(arr);
    return 0;
}
