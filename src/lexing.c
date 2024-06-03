/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-matisse.dufour
** File description:
** lexing.c
*/

#include "my.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

static bool check_item(char c)
{
    char *item = " ;|()><'\"\\\t\n*[]&!`";

    for (int i = 0; item[i]; i++) {
        if (item[i] == c)
            return true;
    }
    return false;
}

static void build_token_item(token_t **token_list, char *str, int i)
{
    token_t *token = malloc(sizeof(token_t));

    token->sep = str[i];
    token->arg = NULL;
    token->next = *token_list;
    *token_list = token;
}

static void build_token_arg(token_t **token_list, char *str, int i, int index)
{
    token_t *token;
    int j = index;

    if (!i || check_item(str[i - 1]))
        return;
    token = malloc(sizeof(token_t));
    token->sep = 0;
    for (; j < i; j++);
    token->arg = strndup(str+index, j);
    token->next = *token_list;
    *token_list = token;
}


token_t **init_token_list(char *str)
{
    int index = 0;
    token_t **token_list = malloc(sizeof(token_t *));

    *token_list = NULL;
    for (int i = 0; str[i]; i++) {
        if (check_item(str[i])) {
            build_token_arg(token_list, str, i, index);
            index = i + 1;
            build_token_item(token_list, str, i);
        }
    }
    return token_list;
}
