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
    return 0;
}

token_t *check_alias(token_t *token, garbage_t *garbage)
{
    alias_t *current = garbage->alias;

    if (token == NULL || token->arg == NULL || garbage->alias == NULL)
        return token;
    for (; current; current = current->next) {
        if (my_strcmp(current->name, token->arg) == 0) {
            return insert_node(token, current->com, garbage);
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

void delete_alias(alias_t *current, alias_t *prev, garbage_t *garbage)
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

static void add_alias(char *name, char *value,
    garbage_t *garbage, alias_t *add)
{
    add->name = my_strdup(name);
    add->com = my_strdup(value);
    add->next = garbage->alias;
    garbage->alias = add;
    garbage->return_value = 0;
}

static int already_exist_alias(char *var, char *value,
    garbage_t *garbage)
{
    alias_t *current = garbage->alias;

    for (; current != NULL; current = current->next) {
        if (strcmp(var, current->name) == 0) {
            free(current->name);
            free(current->com);
            current->name = my_strdup(var);
            current->com = my_strdup(value);
            return 1;
        }
    }
    return 0;
}

int set_alias(char *str, char ***env, garbage_t *garbage)
{
    alias_t *add;
    char **command = my_str_to_array(str, " ");
    char *name = my_strdup(command[1]);
    char *value;

    if (name == NULL) {
        free_array(command);
        return print_alias(garbage);
    }
    if (already_exist_alias(name, command[2], garbage) == 1) {
        free_array(command);
        return 0;
    }
    add = malloc(sizeof(alias_t));
    add_alias(name, command[2], garbage, add);
    free_array(command);
    return 0;
}

int unalias(char *str, char ***env, garbage_t *garbage)
{
    alias_t *current = garbage->alias;
    alias_t *prev = NULL;
    char **command = my_str_to_array(str, " ");
    char *name = command[1];

    for (; current != NULL; current = current->next) {
        if (strcmp(name, current->name) == 0) {
            delete_alias(current, prev, garbage);
            free_array(command);
            return 0;
        }
        prev = current;
    }
    free_array(command);
    return 0;
}
