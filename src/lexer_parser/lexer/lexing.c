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

static int len_nodes(token_t **token_list)
{
    token_t *current = *token_list;
    int compt = 0;

    while (current) {
        compt++;
        current = current->next;
    }
    return compt;
}

static void reverse_list(token_t **token_list)
{
    token_t *prev = NULL;
    token_t *current = *token_list;
    token_t *next = NULL;

    if (len_nodes(token_list) <= 0) {
        return;
    }
    while (current) {
        next = current->next;
        current->prev = next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *token_list = prev;
    (*token_list)->prev = NULL;
}

static bool check_item(char c)
{
    char item[] = " ;|()><'\"\\\t\n*[]&`?=";

    if (c == '\0')
        return true;
    for (int i = 0; item[i]; i++) {
        if (item[i] == c)
            return true;
    }
    return false;
}

static void build_token_item(token_t **token_list, char *str, int i)
{
    token_t *token = gmalloc(sizeof(token_t));

    token->sep = str[i];
    token->arg = NULL;
    if (*token_list == NULL)
        token->index = 0;
    else
        token->index = (*token_list)->index + 1;
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
    token = gmalloc(sizeof(token_t));
    token->sep = 0;
    for (j = 0; tmp[j] && !check_item(tmp[j]); j++);
    token->arg = my_gstrndup(tmp, j);
    if (*token_list == NULL)
        token->index = 0;
    else
        token->index = (*token_list)->index + 1;
    token->next = *token_list;
    *token_list = token;
}

token_t **init_token_list(char *str)
{
    int index = 0;
    int i;
    token_t **token_list = gmalloc(sizeof(token_t *));

    *token_list = NULL;
    for (i = 0; i <= my_strlen(str); i++) {
        if (check_item(str[i])) {
            build_token_arg(token_list, str, i, index);
            index = i + 1;
            build_token_item(token_list, str, i);
        }
    }
    reverse_list(token_list);
    return token_list;
}
