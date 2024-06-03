/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-nicolas.dumetz
** File description:
** history_arrows.c
*/

#include "minishell.h"
#include <stdlib.h>
#include <string.h>

void history_up(history_t **tmp, history_t **history)
{
    if (*tmp == NULL && *history == NULL)
        return;
    if (*tmp == NULL) {
        *tmp = malloc(sizeof(history_t));
        memcpy(*tmp, *history, sizeof(history_t));
        (*tmp)->command = my_strdup((*history)->command);
    } else if (*tmp != NULL && (*tmp)->next != NULL) {
        memcpy(*tmp, (*tmp)->next, sizeof(history_t));
        (*tmp)->command = my_strdup((*tmp)->next->command);
    } else {
        memcpy(*tmp, (*tmp)->prev->next, sizeof(history_t));
        (*tmp)->command = my_strdup((*tmp)->prev->next->command);
    }
}

void history_down(history_t **tmp)
{
    if (*tmp == NULL)
        return;
    else if (*tmp != NULL && (*tmp)->prev != NULL) {
        memcpy(*tmp, (*tmp)->prev, sizeof(history_t));
        (*tmp)->command = my_strdup((*tmp)->prev->command);
    } else {
        free((*tmp)->command);
        *tmp = NULL;
    }
}