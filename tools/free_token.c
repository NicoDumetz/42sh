/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-matisse.dufour
** File description:
** tab_len.c
*/

#include "minishell.h"

void free_token(token_t **token)
{
    free((*token)->arg);
    free(*token);
    *token = NULL;
}
