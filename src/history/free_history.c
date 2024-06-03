/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-nicolas.dumetz
** File description:
** free_history.c
*/

#include "../../include/minishell.h"

void free_history(history_t **history)
{
    history_t *tmp = *history;
    history_t *last_node;

    while (tmp != NULL) {
        last_node = tmp;
        tmp = tmp->next;
        free(last_node->time);
        free(last_node->command);
        free(last_node);
    }
    *history = NULL;
}
