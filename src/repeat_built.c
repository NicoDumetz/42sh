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


static int is_num(char *str)
{
    int i = 0;

    for (i = 0; str[i] && (str[i] == '-' || str[i] == '+'); i++);
    for (; str[i]; i++)
        if (str[i] > '9' || str[i] < '0')
        return 0;
    return 1;
}

token_t *del_head(token_t **token_list)
{
    token_t *next = NULL;

    if (token_list == NULL || *token_list == NULL)
        return NULL;
    next = (*token_list)->next;
    if (next)
        next->prev = NULL;
    free_token(*token_list);
    *token_list = next;
    return next;
}

int find_value_repeat(token_t **token_list)
{
    int value = 0;

    if (*token_list != NULL && (*token_list)->arg != NULL &&
        is_num((*token_list)->arg)) {
        value = my_getnbr((*token_list)->arg);
    } else {
        fprintf(stderr, "repeat: Too few arguments\n");
        return -1;
    }
    del_head(token_list);
    while (*token_list && (!(*token_list)->arg)) {
        del_head(token_list);
        if (*token_list == NULL)
            break;
    }
    if (*token_list == NULL) {
        fprintf(stderr, "repeat: Too few arguments.\n");
        return -1;
    }
    return value;
}

int del_repeat(token_t **token_list)
{
    if (token_list == NULL || *token_list == NULL) {
        fprintf(stderr, "repeat: Too few arguments.\n");
        return -1;
    }
    del_head(token_list);
    while (*token_list) {
        if ((*token_list)->arg && !(*token_list)->sep)
            return find_value_repeat(token_list);
        del_head(token_list);
    }
    fprintf(stderr, "repeat: Too few arguments.\n");
    return -1;
}

int find_repeat(pipeline_t *pipeline, garbage_t *garbage)
{
    int r = 1;

    if (pipeline == NULL || pipeline->token_list == NULL) {
        return -1;
    }
    while ((*pipeline->token_list)->sep)
        del_head(pipeline->token_list);
    if ((*pipeline->token_list)->arg &&
        my_strcmp((*pipeline->token_list)->arg, "repeat") == 0)
        r = del_repeat(pipeline->token_list);
    if (r < 0) {
        garbage->return_value = 1;
        return -1;
    }
    if (r < 0)
        return 0;
    return r;
}

int repeat_built(
    char *, char ***, garbage_t *garbage, pipeline_t *pipeline)
{
    int r = find_repeat(pipeline, garbage);
    int save_fd = 0;

    reset_index(pipeline);
    if (r < 0) {
        garbage->return_value = 1;
        return (1);
    }
    for (int i = 0; i < r; i++) {
        save_fd = dup(pipeline->input);
        execute_semicolon(garbage, pipeline);
        pipeline->input = save_fd;
    }
    close(pipeline->input);
    return (0);
}
