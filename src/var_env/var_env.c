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

static char *extract_var_name(const char *line)
{
    char *name = malloc(sizeof(char) * my_strlen(line));
    int i;

    if (name == NULL)
        return NULL;
    for (i = 0; line[i] && line[i] != '='; i++)
        name[i] = line[i];
    name[i] = '\0';
    return name;
}

static char *extract_var_value(const char *line)
{
    int i;

    for (i = 0; line[i] && line[i] != '='; i++);
    if (line[i] == '\0')
        return NULL;
    i++;
    return strdup(&line[i]);
}

char *remove_quotes(const char *str)
{
    int len = 0;
    char *new_str = NULL;
    int j = 0;
    int i = 0;

    if (str == NULL)
        return NULL;
    len = my_strlen(str);
    new_str = malloc(sizeof(char) * (len + 1));
    for (i = 0; i < len; i++) {
        if (str[i] != '"' && str[i] != '\n') {
            new_str[j] = str[i];
            j++;
        }
    }
    new_str[j] = '\0';
    return new_str;
}

static char *check_var(char *line, token_t *token)
{
    char *new_arg = remove_quotes(token->arg);
    char *var_name = extract_var_name(line);
    char *var_value = extract_var_value(line);

    if (var_name == NULL || var_value == NULL) {
        free(var_name);
        free(var_value);
        free(new_arg);
        return NULL;
    }
    if (strcmp(new_arg + 1, var_name) == 0) {
        free(var_name);
        free(new_arg);
        return var_value;
    }
    free(var_name);
    free(var_value);
    free(new_arg);
    return NULL;
}

int check_varenv(token_t *token, garbage_t *garbage, pipeline_t *pipeline)
{
    char *value;

    if (token == NULL || token->arg == NULL || token->arg[0] != '$')
        return 0;
    if (check_spe_var(token, pipeline, garbage) == 1)
        return 0;
    for (int i = 0; garbage->env[0][i]; i++) {
        value = check_var(garbage->env[0][i], token);
        if (value != NULL) {
            insert_node(token, value, 1, pipeline);
            free(value);
            return 0;
        }
    }
    return 1;
}

token_t *manage_alias(token_t *token, garbage_t *garbage,
    pipeline_t *pipeline)
{
    if (token->arg) {
        if (check_alias_onpip(pipeline) == 0)
            token = check_alias(token, garbage, pipeline);
    }
    return token;
}

token_t *manage_variable(token_t *token, garbage_t *garbage,
    pipeline_t *pipeline)
{
    int ret;
    int env;

    if (token->arg) {
        ret = 0;
        env = 0;
        if (token->arg[0] == '$') {
            ret = check_local(token, garbage, pipeline);
            env = check_varenv(token, garbage, pipeline);
        }
        if (ret == 1 && env == 1) {
            fprintf(stderr, "%s: Undefined variable.\n", token->arg + 1);
            garbage->execute = 1;
            garbage->return_value = 1;
        }
    }
    return token;
}
