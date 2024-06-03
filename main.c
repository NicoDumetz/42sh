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

static void ttycheck(void)
{
    if (isatty(STDIN_FILENO))
        write(1, "$> ", 3);
}

static void travel_command(char *str, char ***env, int *return_value,
    garbage_t *garbage)
{
    char **command = my_str_to_array(str, ";");

    garbage->command = command;
    for (int i = 0; command[i]; i++) {
        format_str(command[i]);
        if (my_strlen(command[i]) == 0)
            continue;
        *return_value = pipe_handling(command[i], env, garbage);
    }
    freeing(0, command);
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
    garbage.alias = old->alias;
    garbage.local = old->local;
    garbage.pipeline = init_pipeline(garbage.raw_command);
    return garbage;
}

int main(int argc, char **argv, char **env)
{
    char *str = 0;
    size_t len = 0;
    garbage_t garbage;

    env = copy_env(env);
    garbage.env = &env;
    garbage.alias = NULL;
    garbage.local = NULL;
    ttycheck();
    while (getline(&str, &len, stdin) != -1 && my_strcmp(str, "exit\n")) {
        garbage = init_garbage(&str, &garbage);
        process_execution(&garbage, garbage.pipeline);
        ttycheck();
    }
    freeing(str, env);
    return garbage.return_value;
}
