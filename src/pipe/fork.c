/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell2-matisse.dufour
** File description:
** fork.c
*/
#include "minishell.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static int fork_execution(char *str, char ***env, char **pipes,
    garbage_t *garbage)
{
    int return_value = redirection(str, env, garbage->save_out, garbage);

    freeing(*garbage->line, garbage->command);
    freeing(0, *garbage->env);
    freeing(0, pipes);
    close(garbage->save_in);
    close(garbage->save_out);
    return return_value;
}

void fork_pipes(char **pipes, int pipeline[][2], int num_pipe,
    garbage_t *garbage)
{
    pid_t pid;

    for (int i = 0; i < num_pipe - 1; i++) {
        pipe(pipeline[i]);
        pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0) {
            pipe_redirect(i, num_pipe, pipeline);
            exit(fork_execution(pipes[i], garbage->env, pipes, garbage));
        }
        if (i > 0) {
            close(pipeline[i - 1][0]);
            close(pipeline[i - 1][1]);
        }
    }
}
