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

static bool is_first_node_correct(garbage_t *garbage, pipeline_t *pipeline)
{
    if (!pipeline)
        return false;
    if (!pipeline->token_list && !strcmp(pipeline->sep, ";"))
        return true;
    else {
        free_pipeline(garbage->pipeline);
        fprintf(2, "%s", ERR_NULL_COMMAND);
        return false;
    }
    return true;
}

void process_execution(garbage_t *garbage, pipeline_t **pipeline)
{
    if (!pipeline || !is_first_node_correct(garbage, *pipeline))
        return;
}
