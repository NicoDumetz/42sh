/*
** EPITECH PROJECT, 2024
** manage
** File description:
** manage
*/

#include "my.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

static int del_alias(char *name, garbage_t *garbage)
{
    alias_t *current = garbage->alias;
    alias_t *prev = NULL;

    for (; current != NULL; current = current->next) {
        if (strcmp(name, current->name) == 0) {
            delete_alias(current, prev, garbage);
            return 1;
        }
        prev = current;
    }
    return 1;
}

int len_alias(garbage_t *garbage)
{
    alias_t *current = garbage->alias;
    int compt = 0;

    if (current == NULL)
        return 0;
    for (; current; current = current->next) {
        compt++;
        if (compt > 1000)
            del_alias(current->name, garbage);
    }
    return compt;
}

int check_alias_onpip(pipeline_t *pipeline)
{
    token_t *current = *pipeline->token_list;

    for (; current; current = current->next) {
        if (current->arg && (strcmp(current->arg, "alias") == 0 ||
            strcmp(current->arg, "unalias") == 0))
            return 1;
    }
    return 0;
}

void reset_index(pipeline_t *pip)
{
    token_t *current = *pip->token_list;

    for (int i = 0; current; current = current->next) {
        current->index = i;
        i++;
    }
}
