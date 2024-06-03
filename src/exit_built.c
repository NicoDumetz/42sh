/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-matisse.dufour
** File description:
** env.c
*/

#include <stdlib.h>
#include <unistd.h>
#include "my.h"
#include "minishell.h"

int exit_built(char *, char ***, garbage_t *garbage, pipeline_t *)
{
    int save_exit = garbage->return_value;

    cleanup(garbage);
    free_pipeline(garbage->pipeline);
    exit(save_exit);
}
