/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-nicolas.dumetz
** File description:
** inibitors.c
*/

#include "errors.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

static void delete_node_string(token_t **head)
{
    token_t *next = 0;
    token_t *current = (*head)->next;

    for (; current->sep != '\"'; current = next) {
        if (current->arg)
            free(current->arg);
        next = current->next;
        free(current);
    }
    (*head)->next = current->next;
    free(current);
    if ((*head)->next != NULL)
        (*head)->next->prev = *head;
}

static void fill_string(token_t **head)
{
    token_t *fill = *head;

    for (token_t *current = fill->next; current->sep != '\"';
    current = current->next) {
        if (current->sep)
            strncat(fill->arg, &current->sep, 1);
        else
            strcat(fill->arg, current->arg);
    }
}

static int string(token_t **head)
{
    token_t *current = (*head)->next;
    int len = 0;

    for (; current && current->sep != '\"'; current = current->next);
    if (current == NULL) {
        write(2, STR_ERROR, strlen(STR_ERROR));
        return 1;
    }
    for (current = (*head)->next; current->sep != '\"';
    current = current->next)
        len += (current->sep == 0) ? strlen(current->arg) : 1;
    (*head)->sep = 0;
    free((*head)->arg);
    (*head)->arg = malloc(len + 1);
    (*head)->arg[0] = '\0';
    fill_string(head);
    delete_node_string(head);
    for (token_t *current = (*head)->next; current; current = current->next)
        current->index = current->prev->index + 1;
    return 0;
}

static void concat_arg(token_t *current)
{
    if (current->prev && current->prev->arg)
        my_strcat(current->arg, current->prev->arg);
    if (current->next->sep)
        my_strncat(current->arg, &current->next->sep, 1);
    else
        my_strcat(current->arg, current->next->arg);
    if (current->next->sep && current->next->next && current->next->next->arg)
        my_strcat(current->arg, current->next->next->arg);
}

static void free_node(token_t *token)
{
    if (token->arg)
        free(token->arg);
    free(token);
}

static void delete_head(pipeline_t *pipeline, token_t *current)
{
    token_t *prev = current->prev;

    if (!(current->prev && current->prev->arg))
        return;
    current->prev = prev->prev;
    if (current->prev)
        current->prev->next = current;
    else
        *pipeline->token_list = current;
    free_node(prev);
}

static void delete_node_backslash(pipeline_t *pipeline, token_t *current)
{
    token_t *save;

    delete_head(pipeline, current);
    save = current->next;
    current->next = save->next;
    if (current->next)
        current->next->prev = current;
    free_node(save);
    if (current->next == NULL || current->next->sep)
        return;
    save = current->next;
    current->next = save->next;
    if (current->next)
        current->next->prev = current;
    free_node(save);
}

static void reset_inib_index(pipeline_t *pipeline)
{
    int index = 0;
    token_t *current = *pipeline->token_list;

    for (; current; current = current->next) {
        current->index = index;
        index++;
    }
}

static int backslash(pipeline_t *pipeline, token_t **head)
{
    token_t *current = *head;
    int new_len = 0;

    if (current->next == 0) {
        write(2, "How is that even possible?\n", 27);
        return 1;
    }
    if (current->prev && current->prev->arg != 0)
        new_len += my_strlen(current->prev->arg);
    new_len += (current->next->sep == 0) ? my_strlen(current->next->arg) : 1;
    if (current->next->sep && current->next->next && current->next->next->arg)
        new_len += my_strlen(current->next->next->arg);
    current->sep = 0;
    current->arg = malloc(new_len + 1);
    current->arg[0] = '\0';
    concat_arg(current);
    delete_node_backslash(pipeline, current);
    reset_inib_index(pipeline);
    return 0;
}

int inibitors(pipeline_t *pipeline, garbage_t *garbage)
{
    int return_value = 0;
    token_t *current;

    if (pipeline->token_list == 0)
        return 0;
    current = *pipeline->token_list;
    for (; current; current = current->next) {
        if (current->sep == '\\')
            return_value = backslash(pipeline, &current);
        if (current->sep == '\"')
            return_value = string(&current);
        if (return_value) {
            garbage->return_value = return_value;
            return return_value;
        }
    }
    return 0;
}
