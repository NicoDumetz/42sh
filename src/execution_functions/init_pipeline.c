/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-matisse.dufour
** File description:
** init_pipeline.c
*/

#include "my.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

void free_pipeline(pipeline_t **pipeline)
{
    pipeline_t *tmp = *pipeline;

    for (; tmp; tmp = tmp->next) {
        if (tmp->token_list)
            free_token_list(tmp->token_list);
        if (tmp->sep)
            free(tmp->sep);
    }
    free(pipeline);
    pipeline = NULL;
}

static void reverse_pipeline(pipeline_t **commands)
{
    pipeline_t *prev = NULL;
    pipeline_t *current = *commands;
    pipeline_t *next = NULL;

    while (current) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *commands = prev;
}

static bool check_sep(char *str, int i, int index)
{
    char item[] = ";|><&\n";

    if (i == index && i != 0)
        return false;
    for (int j = 0; item[j]; j++) {
        if (item[j] == str[i])
            return true;
    }
    return false;
}

static char *get_sep(char const *str, int *i, int *index)
{
    char *sep = malloc_str(2);

    if (!sep)
        return NULL;
    if (str[*i] == '\0')
        sep[0] = '\n';
    else
        sep[0] = str[*i];
    if (str[*i] == '|' || str[*i] == '&' ||
        str[*i] == '<' || str[*i] == '>') {
        if (str[*i] == str[*i + 1]) {
            sep[1] = str[*i];
            // *i += 1;
            *index += 1;
        }
    }
    return sep;
}

static pipeline_t *build_node(char *str, int *i, int *index)
{
    char *command = NULL;
    pipeline_t *node = malloc(sizeof(pipeline_t));

    command = malloc_str(*i - *index);
    command = my_strncpy(command, &str[*index], *i - *index);
    if (*i == 0)
        node->token_list = NULL;
    else
        node->token_list = init_token_list(command);
    free(command);
    node->sep = get_sep(str, i, index);
    node->return_value = -1;
    node->pid = 0;
    node->input = STDIN_FILENO;
    node->output = STDOUT_FILENO;
    node->error_output = STDERR_FILENO;
    return node;
}

static void skip_parenthesis(char const *str, int *i)
{
    int nb = 0;

    if (str[*i] == '(') {
        nb++;
        *i += 1;
    }
    for (; str[*i] && nb; *i += 1) {
        if (str[*i] == ')')
            nb--;
        if (str[*i] == '(')
            nb++;
    }
}

static void skip_quotes(char *str, int *i)
{
    int nb = 0;

    if (str[*i] == '"') {
        nb++;
        *i += 1;
    }
    for (; str[*i] && nb; *i += 1) {
        if (str[*i] == '"')
            nb--;
    }
}

static void skip_backticks(char *str, int *i)
{
    int nb = 0;

    if (str[*i] == '`') {
        nb++;
        *i += 1;
    }
    for (; str[*i] && nb; *i += 1) {
        if (str[*i] == '`')
            nb--;
    }
}

static void skip_features(char *str, int *i)
{
    skip_parenthesis(str, i);
    skip_quotes(str, i);
    skip_backticks(str, i);
}

pipeline_t **init_pipeline(char *str)
{
    pipeline_t **pipeline = malloc(sizeof(pipeline_t *));
    pipeline_t *node = NULL;
    int i = 0;
    int index = 0;

    if (!pipeline)
        return NULL;
    *pipeline = NULL;
    for (i = 0; i <= strlen(str); i++) {
        skip_features(str, &i);
        if (check_sep(str, i, index)) {
            node = build_node(str, &i, &index);
            node->next = *pipeline;
            *pipeline = node;
            index = i + 1;
        }
    }
    reverse_pipeline(pipeline);
    return pipeline;
}
