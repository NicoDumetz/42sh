/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-matisse.dufour
** File description:
** lexing_features.c
*/

#include "my.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void lexing_features(garbage_t *garbage, token_t **token_list)
{
    int i = 0;

    for (i = 0; l_tab[i].sep != 0 && sep != l_tab[i].sep; i++);
    if (l_tab[i].sep == 0)
        return EXIT_FAILURE;
    l_tab[i].feature(garbage, token_list);
    return EXIT_SUCCESS;
}
