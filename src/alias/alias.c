/*
** EPITECH PROJECT, 2024
** manage alias
** File description:
** alias manage
*/

#include "my.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

static int print_alias(garbage_t *garbage)
{
    alias_t *current = garbage->alias;

    if (current == NULL)
        return 0;
    for (; current; current = current->next) {
        printf("%s\t%s\n", current->name, current->com);
    }
}

int set_alias(char *name, char *command, garbage_t *garbage)
{
    alias_t *add = malloc(sizeof(alias_t));

    if (add == NULL)
        return 1;
    if (name == NULL)
        return print_alias(garbage);
    add->name = my_strdup(name);
    add->com = my_strdup(command);
    add->next = garbage->alias;
    garbage->alias = add;
    garbage->return_value = 0;
    return 0;
}

char *check_alias(char *token, garbage_t *garbage)
{
    alias_t *current = garbage->alias;

    if (token == NULL)
        return token;
    for (; current; current = current->next) {
        if (my_strcmp(current->name, token) == 0) {
            free(token);
            return my_strdup(current->com);
        }
    }
    return token;
}

void free_alias(garbage_t *garbage)
{
    alias_t *current = garbage->alias;
    alias_t *next;

    for (; current != NULL; current = next) {
        next = current->next;
        if (current->name != NULL)
            free(current->name);
        if (current->com != NULL)
            free(current->com);
        free(current);
    }
}

static void delete_alias(alias_t *current, alias_t *prev, garbage_t *garbage)
{
    if (prev == NULL) {
        garbage->alias = current->next;
    } else {
        prev->next = current->next;
    }
    free(current->name);
    free(current->com);
    free(current);
    return;
}

void unalias(char *name, garbage_t *garbage)
{
    alias_t *current = garbage->alias;
    alias_t *prev = NULL;

    for (; current != NULL; current = current->next) {
        if (strcmp(name, current->name) == 0) {
            delete_alias(current, prev, garbage);
            return;
        }
        prev = current;
    }
    return;
}
