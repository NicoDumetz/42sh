/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-matisse.dufour
** File description:
** init_pipeline.c
*/

#include "minishell.h"
#include "../../include/errors.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

static void print_error_redirection(pipeline_t *pipeline)
{
    if ((!pipeline->next) &&
        (!strcmp(pipeline->sep, "<") || !strcmp(pipeline->sep, ">") ||
        !strcmp(pipeline->sep, "<<") || !strcmp(pipeline->sep, ">>")))
        fprintf(stderr, "%s", ERR_MISSING_NAME_REDIRECT);
    else
        fprintf(stderr, "%s", ERR_NULL_COMMAND);
}

static bool is_node_correct(garbage_t *garbage, pipeline_t *pipeline)
{
    if (pipeline->token_list && pipeline->next && pipeline->next->token_list)
        return true;
    else {
        print_error_redirection(pipeline);
        free_pipeline(garbage->pipeline);
        garbage->return_value = 1;
        return false;
    }
    return true;
}

static bool is_pipeline_correct(garbage_t *garbage, pipeline_t *pipeline)
{
    if (!pipeline->token_list && !strcmp(pipeline->sep, "&&"))
        pipeline = pipeline->next;
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
    static int error = 0;
    int i = 0;

    if (pipeline->sep[0] == ';' || pipeline->sep[0] == '\n' ||
    pipeline == *garbage->pipeline)
        error = 0;
    if (!error)
        error = inibitors(pipeline, garbage);
    for (i = 0; r_tab[i].sep && strcmp(r_tab[i].sep, pipeline->sep); i++);
    if (r_tab[i].sep == 0 || error)
        return pipeline;
    pipeline = r_tab[i].redirection(garbage, pipeline);
    return pipeline;
}

static void execute_pipeline(garbage_t *garbage, pipeline_t *pipeline)
{
    for (; pipeline; pipeline = pipeline->next)
        pipeline = process_separator(garbage, pipeline);
}

void process_execution(garbage_t *garbage, pipeline_t **pipeline)
{
    if (!pipeline || !is_pipeline_correct(garbage, *pipeline))
        return;
    execute_pipeline(garbage, *pipeline);
}
