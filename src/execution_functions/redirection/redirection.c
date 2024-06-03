/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell2-matisse.dufour
** File description:
** redirection.c
*/
#include "minishell.h"
#include "my.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void write_error(char *name)
{
    char *error = strerror(errno);

    if (error == 0) {
        return;
    }
    write(2, name, my_strlen(name));
    write(2, ": ", 2);
    write(2, error, my_strlen(error));
    write(2, ".\n", 2);
}

static void set_fd_out(char *str, pipeline_t *node)
{
    int mode = (O_CREAT | O_WRONLY | O_TRUNC);
    int mode_2 = (O_CREAT | O_WRONLY | O_APPEND);

    if (str == 0) {
        node->output = -1;
        return;
    }
    if (!strcmp(node->sep, ">"))
        node->output = open(str, mode, 0644);
    if (!strcmp(node->sep, ">>"))
        node->output = open(str, mode_2, 0644);
    if (node->output == -1)
        return write_error(str);
}

static void set_fd_in(char *str, pipeline_t *pipeline)
{
    if (!strcmp(pipeline->sep, "<<"))
        pipeline->next->input = find_stdin(str);
    else
        pipeline->next->input = open(str, O_RDONLY);
    if (pipeline->next->input == -1)
        return write_error(str);
    pipeline->next->token_list = pipeline->token_list;
}

pipeline_t *execute_redirection(garbage_t *garbage, pipeline_t *pipeline)
{
    char *str = NULL;

    globbings(garbage, pipeline->token_list);
    str = token_to_str(*pipeline->next->token_list);
    clean_space(str);
    
    if (!strcmp(pipeline->sep, "<") || !strcmp(pipeline->sep, "<<")) {
        set_fd_in(str, pipeline);
        free(str);
        return pipeline;
    }
    if (!strcmp(pipeline->sep, ">") || !strcmp(pipeline->sep, ">>")) {
        set_fd_out(str, pipeline);
        garbage->return_value = new_process(pipeline,
            token_to_str_array(*pipeline->token_list,
            get_token_list_size(
                *pipeline->token_list)), *garbage->env, garbage);
            free(str);
            return pipeline->next;
    }
    return NULL;
}
