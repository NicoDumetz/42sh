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
        }
        if (i > 0) {
            close(pipeline[i - 1][0]);
            close(pipeline[i - 1][1]);
        }
    }
}
