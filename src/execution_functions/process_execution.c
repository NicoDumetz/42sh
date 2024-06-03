/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-matisse.dufour
** File description:
** init_pipeline.c
*/

#include "my.h"
#include "minishell.h"
#include "../../include/errors.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>


static bool is_node_correct(garbage_t *garbage, pipeline_t *pipeline)
{
    if (pipeline->token_list || pipeline->next || pipeline->token_list)
        return true;
    else {
        free_pipeline(garbage->pipeline);
        fprintf(stderr, "%s", ERR_NULL_COMMAND);
        return false;
    }
    return true;
}

static bool is_pipeline_correct(garbage_t *garbage, pipeline_t *pipeline)
{
    for (; pipeline; pipeline = pipeline->next) {
        if (!strcmp(pipeline->sep, "&") || !strcmp(pipeline->sep, ";") ||
            !strcmp(pipeline->sep, "\n") || !pipeline->sep[0])
            continue;
        if (!is_node_correct(garbage, pipeline))
            return false;
    }
    return true;
}

void process_execution(garbage_t *garbage, pipeline_t **pipeline)
{
    if (!pipeline || !is_pipeline_correct(garbage, *pipeline))
        return;
    printf("\n\n\n\t\t--ALL GOOD SIR--\n\n\n");
}
