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

int check_varenv(token_t *token, garbage_t *garbage, pipeline_t *pipeline)
{
    char *value;
    token_t *new;

    if (token == NULL || token->arg == NULL || token->arg[0] != '$')
        return 0;
    for (int i = 0; garbage->env[0][i]; i++) {
        value = check_var(garbage->env[0][i], token, garbage);
        if (value != NULL) {
            new = insert_node(token, value, garbage, pipeline);
            free(value);
            return 0;
        }
    }
    return 1;
}

token_t *manage_variable(token_t *token, garbage_t *garbage,
    pipeline_t *pipeline)
{
    int ret;
    int env;

    if (token->arg) {
            ret = 0;
            env = 0;
            if (check_alias_onpip(pipeline) == 0)
                token = check_alias(token, garbage, pipeline);
            if (token->arg[0] == '$') {
                ret = check_local(token, garbage, pipeline);
                env = check_varenv(token, garbage, pipeline);
            }
            if (ret == 1 && env == 1) {
                fprintf(stderr, "%s: Undefined variable.\n", token->arg + 1);
                garbage->return_value = 1;
            }
    }
    return token;
}
