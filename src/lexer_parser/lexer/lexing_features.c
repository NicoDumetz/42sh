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

static bool process_lexing_sep(garbage_t *garbage, token_t **token_list)
{
    token_t *token = *token_list;
    int i = 0;

    for (i = 0; l_tab[i].sep != 0 && l_tab[i].sep != token->sep; i++);
    if (l_tab[i].sep == 0)
        return false;
    l_tab[i].lexing(garbage, token_list);
    return true;
}

void lexing_features(garbage_t *garbage, token_t **token_list)
{
    token_t *token = *token_list;

    for (; token; token = token->next) {
        if (process_lexing_sep(garbage, &token))
            return;
    }
}
