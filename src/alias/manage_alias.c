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
    alias_t *prev = NULL;
    alias_t *next;

    if (current == NULL)
        return 0;
    for (; current; current = current->next) {
        compt++;
        if (compt > 1000)
            del_alias(current->name, garbage);
        prev = current;
    }
    return compt;
}

void reset_index(garbage_t *garbage)
{
    token_t *current = *garbage->token_list;

    for (int i = 0; current; current = current->next) {
        current->index = i;
        i++;
    }
}
