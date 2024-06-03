/*
** EPITECH PROJECT, 2024
** check value
** File description:
** check value
*/
#include "my.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


int char_is_alpha(char c)
{
    return (c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z') ||
        (c >= '0' && c <= '9') ||
        c == '_';
}

int str_is_alpha(const char *str)
{
    if (str == NULL)
        return 1;
    for (int i = 0; str[i]; i++) {
        if (!char_is_alpha(str[i]))
            return 0;
    }
    return 1;
}

char *pick_token_var(pipeline_t *pip, int who)
{
    token_t *token = *pip->token_list;

    for (; token->sep == ' ' && (token->arg == NULL ||
    strcmp(token->arg, "set") != 0); token = token->next);
    for (token = token->next; token->sep == ' '; token = token->next);
    if (token->arg == NULL)
        return NULL;
    else if (who == 1)
        return token->arg;
    for (token = token->next; token->sep == ' '; token = token->next);
    if (token->sep != '=')
        return NULL;
    for (token = token->next; token->sep == ' '; token = token->next);
    return token->arg;
}
