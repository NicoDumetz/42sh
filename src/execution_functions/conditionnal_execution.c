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

pipeline_t *execute_semicolon(garbage_t *garbage,  pipeline_t *pipeline)
{
    if (!pipeline->token_list) {
        garbage->return_value = EXIT_SUCCESS;
        return pipeline;
    }
    garbage->return_value = new_process(pipeline, token_to_str_array(*pipeline->token_list,
        get_token_list_size(*pipeline->token_list)), *garbage->env);
    return pipeline;
}
