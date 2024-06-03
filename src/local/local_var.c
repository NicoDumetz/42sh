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
#include "errors.h"


static int print_local(garbage_t *garbage)
{
    var_t *current = garbage->local;

    if (current == NULL)
        return 0;
    for (; current; current = current->next) {
        printf("%s\t%s\n", current->var, current->value);
    }
    return 0;
}

int check_local(token_t *token, garbage_t *garbage, pipeline_t *pipeline)
{
    var_t *current = garbage->local;
    char *new_arg = remove_quotes(token->arg);

    if (token == NULL || new_arg == NULL || new_arg[0] != '$')
        return 0;
    for (; current; current = current->next) {
        if (my_strcmp(current->var, new_arg + 1) == 0) {
            insert_node(token, current->value, 1, pipeline);
            free(new_arg);
            return 0;
        }
    }
    free(new_arg);
    return 1;
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

void delete_var(var_t *current, var_t *prev, garbage_t *garbage)
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

static int add_local(char *var, char *value,
    garbage_t *garbage, var_t *add)
{
    add->var = my_strdup(var);
    add->value = my_strdup(value);
    add->next = garbage->local;
    garbage->local = add;
    return 0;
}

static int already_exist_local(char *var, char *value,
    garbage_t *garbage)
{
    var_t *current = garbage->local;

    for (; current != NULL; current = current->next) {
        if (strcmp(var, current->var) == 0) {
            free(current->var);
            free(current->value);
            current->var = my_strdup(var);
            current->value = my_strdup(value);
            return 1;
        }
    }
    return 0;
}

int set_local(char *, char ***, garbage_t *garbage, pipeline_t *pip)
{
    var_t *add;
    char *var = pick_token_var(pip, 1);
    char *value = pick_token_var(pip, 2);

    var_len(garbage);
    if (char_is_alpha(var[0]) == 0) {
        write(2, VAR_BEG, strlen(VAR_BEG));
        return 1;
    }
    if (str_is_alpha(var) == 0) {
        write(2, VAR, strlen(VAR));
        return 1;
    }
    if (var == NULL)
        return print_local(garbage);
    if (already_exist_local(var, value, garbage) == 1)
        return 0;
    add = malloc(sizeof(var_t));
    return add_local(var, value, garbage, add);
}

int unset_var(char *str, char ***, garbage_t *garbage, pipeline_t *)
{
    var_t *current = garbage->local;
    var_t *prev = NULL;
    char **command = my_str_to_array(str, " ");
    char *name = command[1];

    for (; current != NULL; current = current->next) {
        if (strcmp(name, current->var) == 0) {
            delete_var(current, prev, garbage);
            free_array(command);
            return 1;
        }
        prev = current;
    }
    free_array(command);
    return 0;
}
