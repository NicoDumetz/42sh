/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell2-matisse.dufour
** File description:
** pipe.c
*/
#include "minishell.h"
#include "my.h"
#include <sys/wait.h>
#include <unistd.h>

static int count_pipe(char **pipe)
{
    int i = 0;

    for (; pipe[i]; i++);
    return i;
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

static void clean_pipes(char **pipes)
{
    for (int i = 0; pipes[i]; i++)
        format_str(pipes[i]);
}

static void last_redirect(int num_pipe, int pipeline[][2])
{
    if (num_pipe <= 1)
        return;
    dup2(pipeline[num_pipe - 2][0], STDIN_FILENO);
    close(pipeline[num_pipe - 2][0]);
    close(pipeline[num_pipe - 2][1]);
}

void pipe_redirect(int i, int num_pipe, int pipeline[][2])
{
    if (i > 0) {
        dup2(pipeline[i - 1][0], STDIN_FILENO);
        close(pipeline[i - 1][0]);
        close(pipeline[i - 1][1]);
    }
    dup2(pipeline[i][1], STDOUT_FILENO);
    close(pipeline[i][0]);
    close(pipeline[i][1]);
}

static void reset_fd(int save_in, int save_out)
{
    dup2(save_in, STDIN_FILENO);
    dup2(save_out, STDOUT_FILENO);
    close(save_in);
    close(save_out);
}

int pipe_handling(char *str, char ***env, garbage_t *garbage)
{
    char **pipes = my_str_to_array(str, "|");
    int num_pipe = count_pipe(pipes);
    int pipeline[num_pipe - 1][2];
    int result = 0;

    garbage->save_in = dup(STDIN_FILENO);
    garbage->save_out = dup(STDOUT_FILENO);
    clean_pipes(pipes);
    if (command_errors(str, pipes, garbage->save_in, garbage->save_out))
        return 1;
    fork_pipes(pipes, pipeline, num_pipe, garbage);
    last_redirect(num_pipe, pipeline);
    reset_fd(garbage->save_in, garbage->save_out);
    freeing(0, pipes);
    return result;
}

pipeline_t *execute_pipe(garbage_t *garbage, pipeline_t *commands)
{
    pipeline_t *node = commands;
    int fd[2][2];
    int i = 0;

    for (; node->next && !strcmp(node->next->sep, "|"); node = node->next) {
        pipe(fd[i]);
        node->output = fd[i][1];
        node->next->input = fd[i][0];
        garbage->return_value = new_process(node,
        token_to_str_array(*node->token_list,
        get_token_list_size(*node->token_list)), *garbage->env);
        i = !i ? 1 : 0;
    }
    pipe(fd[i]);
    node->output = fd[i][1];
    node->next->input = fd[i][0];
    garbage->return_value = new_process(node, token_to_str_array(
    *node->token_list, get_token_list_size(*node->token_list)), *garbage->env);
    return node;
}
