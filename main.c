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

int function(char *str, char ***env)
{
    if (my_strncmp(str, "cd", 2) == 0)
        return change_dir(str, env);
    if (my_strncmp(str, "setenv", 6) == 0)
        return set_environnement(str, env);
    if (my_strncmp(str, "unsetenv", 8) == 0)
        return delete_env(str, env);
    if (my_strncmp(str, "env", 3) == 0)
        return show_env(*env);
    return new_process(&str, *env);
}

static void ttycheck(void)
{
    if (isatty(STDIN_FILENO))
        write(1, "$> ", 3);
}

void format_str(char *str)
{
    int i;

    for (i = 0; str[i]; i++) {
        if (str[i] == '\t')
            str[i] = ' ';
    }
    for (i = 0; str[i] && str[i] == ' '; i++);
    my_strcpy(str, str + i);
    if (str[my_strlen(str) - 1] == '\n')
        str[my_strlen(str) - 1] = '\0';
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

static void print_token_list(token_t **token_list)
{
    token_t *token = NULL;

    if (!token) {
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

static void print_pipeline(pipeline_t **pipeline)
{
    pipeline_t *node = *pipeline;

    for (; node; node = node->next) {
        printf("\tSTART PIPE\n");
        print_token_list(node->token_list);
        printf("\tSEPARATOR:\t%s\n", node->sep);
        printf("\n\tEND PIPE\n");
    }
}

static garbage_t init_garbage(char **str, char ***env)
{
    garbage_t garbage;

    garbage.env = env;
    garbage.raw_command = *str;
    garbage.return_value = 0;
    garbage.save_out = STDOUT_FILENO;
    garbage.save_in = STDIN_FILENO;
    garbage.token_list = NULL;
    garbage.alias = NULL;
    garbage.local = NULL;
    garbage.pipeline = init_pipeline(garbage.raw_command);
    print_pipeline(garbage.pipeline);
    // garbage.token_list = init_token_list(garbage.raw_command);
    // print_token_list(garbage.token_list);
    return garbage;
}

int main(int argc, char **argv, char **env)
{
    char *str = 0;
    size_t len = 0;
    garbage_t garbage;

    env = copy_env(env);
    ttycheck();
    while (getline(&str, &len, stdin) != -1 && my_strcmp(str, "exit\n")) {
        garbage = init_garbage(&str, &env);
        process_execution(&garbage, garbage.pipeline);
        // lexing_features(&garbage, garbage.token_list);
        // parsing_function(&garbage, garbage.token_list);
        // free_token_list(garbage.token_list);
        // insert_spaces(&str);
        // travel_command(str, &env, &garbage);
        ttycheck();
    }
    freeing(str, env);
    // freeing(str, env);
    // return return_value;
    return 0;
}
