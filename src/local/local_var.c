/*
** EPITECH PROJECT, 2024
** manage local var
** File description:
** manage local var
*/

#include "my.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


static int print_local(garbage_t *garbage)
{
    var_t *current = garbage->local;

    if (current == NULL)
        return 0;
    for (; current; current = current->next) {
        printf("%s\t%s\n", current->var, current->value);
    }
}

char *check_local(char *token, garbage_t *garbage)
{
    var_t *current = garbage->local;

    if (token == NULL || token[0] != '$')
        return token;
    for (; current; current = current->next) {
        if (my_strcmp(current->var, token + 1) == 0) {
            free(token);
            return my_strdup(current->value);
        }
    }
    return token;
}

void free_var(garbage_t *garbage)
{
    var_t *current = garbage->local;
    var_t *next;

    for (; current != NULL; current = next) {
        next = current->next;
        if (current->var != NULL)
            free(current->var);
        if (current->value != NULL)
            free(current->value);
        free(current);
    }
}

static void delete_var(var_t *current, var_t *prev, garbage_t *garbage)
{
    if (prev == NULL) {
        garbage->local = current->next;
    } else {
        prev->next = current->next;
    }
    free(current->var);
    free(current->value);
    free(current);
    return;
}

static void add_local(char *var, char *value,
    garbage_t *garbage, var_t *add)
{
    add->var = my_strdup(var);
    add->value = my_strdup(value);
    add->next = garbage->local;
    garbage->local = add;
}

int set_local(char *str, char ***env, garbage_t *garbage)
{
    var_t *add = malloc(sizeof(var_t));
    char **command = my_str_to_array(str, " ");
    char *var = command[1];
    char *value;

    if (add == NULL) {
        free_array(command);
        return 1;
    }
    if (var == NULL) {
        free_array(command);
        return print_local(garbage);
    }
    if (command[2] == NULL || command[3] == NULL)
        value = NULL;
    else
        value = command[3];
    add_local(var, value, garbage, add);
    return 0;
}

int unset_var(char *str, char ***env, garbage_t *garbage)
{
    var_t *current = garbage->local;
    var_t *prev = NULL;
    char **command = my_str_to_array(str, " ");
    char *name = command[1];

    for (; current != NULL; current = current->next) {
        if (strcmp(name, current->var) == 0) {
            delete_var(current, prev, garbage);
            return 1;
        }
        prev = current;
    }
    return 1;
}
