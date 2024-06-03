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

static void reverse_list(token_t **token_list)
{
    token_t *prev = NULL;
    token_t *current = *token_list;
    token_t *next = NULL;

    while (current) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *token_list = prev;
}

static bool check_item(char c)
{
    char item[] = " ;|()><'\"\\\t\n*[]&!`";

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
    char *tmp = str + index;
    int j = 0;

    if (!i || check_item(str[i - 1]))
        return;
    token = malloc(sizeof(token_t));
    token->sep = 0;
    for (j = 0; tmp[j] && !check_item(tmp[j]); j++);
    token->arg = strndup(tmp, j);
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
    reverse_list(token_list);
    return token_list;
}
