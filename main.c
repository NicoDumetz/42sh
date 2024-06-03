/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-matisse.dufour
** File description:
** main.c
*/

#include "my.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

void freeing(char *str, char **env)
{
    if (str)
        free(str);
    if (!env)
        return;
    for (int i = 0; env[i]; i++)
        free(env[i]);
    free(env);
}

void ttycheck(void)
{
    if (isatty(STDIN_FILENO))
        printf("$> ");
}

void print_token_list(token_t **token_list)
{
    token_t *token = NULL;

    if (!token_list) {
        printf("empty token list\n");
        return;
    }
    token = *token_list;
    for (; token; token = token->next) {
        if (token->arg)
            printf("\ttoken:%s\n", token->arg);
        if (token->sep)
            printf("\ttoken :%c\n", token->sep);
    }
}

void print_pipeline(pipeline_t **pipeline)
{
    pipeline_t *node = *pipeline;

    for (; node; node = node->next) {
        printf("\n\tSTART PIPE\n");
        print_token_list(node->token_list);
        printf("\tSEPARATOR:\t%s%d\n", node->sep, node->sep[0]);
        printf("\n\tEND PIPE\n");
    }
}

static garbage_t init_garbage(char **str, garbage_t *old)
{
    garbage_t garbage;

    garbage.env = old->env;
    garbage.raw_command = *str;
    garbage.return_value = 0;
    garbage.save_out = STDOUT_FILENO;
    garbage.save_in = STDIN_FILENO;
    garbage.token_list = NULL;
    garbage.history = old->history;
    garbage.alias = old->alias;
    garbage.local = old->local;
    garbage.pipeline = init_pipeline(garbage.raw_command);
    format_variable(&garbage, garbage.pipeline);
    return garbage;
}

static void init_main(garbage_t *garbage, history_t **history, char **str,
    char ***env)
{
    set_non_canonical_mode();
    garbage->history = history;
    garbage->line = str;
    garbage->env = env;
    garbage->alias = NULL;
    garbage->local = NULL;
}

int main(int, char **, char **env)
{
    char *str = 0;
    size_t len = 0;
    garbage_t garbage;
    history_t *history = NULL;

    env = copy_env(env);
    signal(SIGINT, (void (*)(int))sigint_handler);
    init_main(&garbage, &history, &str, &env);
    while (my_getline(&str, &len, garbage.history, stdin) != -1) {
        garbage = init_garbage(&str, &garbage);
        add_history(str, garbage.history);
        if (garbage.return_value == 0)
            process_execution(&garbage, garbage.pipeline);
    }
    freeing(str, env);
    cleanup(&garbage);
    return garbage.return_value;
}
