/*
** EPITECH PROJECT, 2024
** var env
** File description:
** var env
*/

#include "my.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

static char *check_var(char *line, token_t *token, garbage_t *garbage)
{
    char name[my_strlen(line)];
    char *value = malloc(sizeof(char) * my_strlen(line));
    int i;
    int k;

    if (value == NULL)
        return NULL;
    for (i = 0; line[i] && line[i] != '='; i++)
        name[i] = line[i];
    name[i] = '\0';
    i++;
    for (k = 0; line[i]; i++) {
        value[k] = line[i];
        k++;
    }
    value[k] = '\0';
    if (strcmp(token->arg + 1, name) == 0)
        return value;
    free(value);
    return NULL;
}

token_t *check_varenv(token_t *token, garbage_t *garbage)
{
    char *value;
    token_t *new;

    if (token == NULL || token->arg == NULL || token->arg[0] != '$')
        return token;
    for (int i = 0; garbage->env[0][i]; i++) {
        value = check_var(garbage->env[0][i], token, garbage);
        if (value != NULL) {
            new = insert_node(token, value, garbage);
            free(value);
            return new;
        }
    }
    return token;
}

token_t *manage_variable(token_t *token, garbage_t *garbage)
{
    if (token->arg) {
            token = check_alias(token, garbage);
            token = check_local(token, garbage);
            token = check_varenv(token, garbage);
    }
    return token;
}
