/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-matisse.dufour
** File description:
** conditionnal_execution.c
*/

#include "my.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <asm-generic/errno.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

static int segfault_exit(int status)
{
    write(2, "Segmentation fault", 18);
    if (WCOREDUMP(status))
        write(2, " (core dumped)", 14);
    write(2, "\n", 1);
    return 139;
}

static int return_status(int status)
{
    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    if (WIFSIGNALED(status))
        if (WTERMSIG(status) == SIGSEGV)
            return segfault_exit(status);
    return 1;
}

pipeline_t *execute_semicolon(garbage_t *garbage, pipeline_t *pipeline)
{
    char **command;
    int status = 1;

    if (!pipeline->token_list) {
        garbage->return_value = EXIT_SUCCESS;
        return pipeline;
    }
    if (globbings(garbage, pipeline->token_list) == -1)
        return pipeline;
    command = token_to_str_array(*pipeline->token_list,
    get_token_list_size(*pipeline->token_list));
    if (check_built(command, garbage, pipeline) == 1) {
        free_array(command);
        return pipeline;
    }
    garbage->return_value = new_process(
        pipeline, command, *garbage->env, garbage);
    waitpid(pipeline->pid, &status, 0);
    garbage->return_value = return_status(status);
    return pipeline;
}

static pipeline_t *skip_command(pipeline_t *pipeline)
{
    pipeline = pipeline->next;
    for (; pipeline && (strcmp(pipeline->sep, ";") &&
        strcmp(pipeline->sep, "\n") &&
        strcmp(pipeline->sep, "||")); pipeline = pipeline->next);
    return pipeline;
}

pipeline_t *execute_and(garbage_t *garbage, pipeline_t *pipeline)
{
    char **command;
    int status = 1;

    if (!pipeline->token_list) {
        garbage->return_value = EXIT_SUCCESS;
        return pipeline;
    }
    command = token_to_str_array(*pipeline->token_list,
    get_token_list_size(*pipeline->token_list));
    if (check_built(command, garbage, pipeline) == 1)
        return pipeline;
    garbage->return_value = new_process(pipeline, command,
        *garbage->env, garbage);
    waitpid(pipeline->pid, &status, 0);
    garbage->return_value = return_status(status);
    if (garbage->return_value != 0) {
        pipeline = skip_command(pipeline);
    }
    return pipeline;
}

pipeline_t *execute_or(garbage_t *garbage, pipeline_t *pipeline)
{
    char **command;
    int status = 1;

    if (!pipeline->token_list) {
        garbage->return_value = EXIT_SUCCESS;
        return pipeline;
    }
    command = token_to_str_array(*pipeline->token_list,
    get_token_list_size(*pipeline->token_list));
    if (check_built(command, garbage, pipeline) == 1)
        return pipeline;
    garbage->return_value = new_process(pipeline, command,
        *garbage->env, garbage);
    waitpid(pipeline->pid, &status, 0);
    garbage->return_value = return_status(status);
    if (garbage->return_value == 0) {
        pipeline = skip_command(pipeline);
    }
    return pipeline;
}
