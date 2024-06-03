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
        garbage->return_value = 1;
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

static pipeline_t *process_separator(garbage_t *garbage, pipeline_t *pipeline)
{
    int i = 0;

    for (i = 0; r_tab[i].sep && strcmp(r_tab[i].sep, pipeline->sep); i++);
    if (r_tab[i].sep == 0)
        return pipeline;
    pipeline = r_tab[i].redirection(garbage, pipeline);
    return pipeline;
}

static void execute_pipeline(garbage_t *garbage, pipeline_t *pipeline)
{
    for (;pipeline ;pipeline = pipeline->next)
        pipeline = process_separator(garbage, pipeline);
}

void process_execution(garbage_t *garbage, pipeline_t **pipeline)
{
    if (!pipeline || !is_pipeline_correct(garbage, *pipeline))
        return;
    execute_pipeline(garbage, *pipeline);
}
