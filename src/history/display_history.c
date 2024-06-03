/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-nicolas.dumetz
** File description:
** display_history.c
*/

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

void clear_history(history_t **history)
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

void show_reverse_history(history_t **history, int *status_flags)
{
    history_t *tmp = *history;
    int counter = 0;

    while (tmp != NULL && counter < status_flags[3]) {
        if (status_flags[1] == 0)
            printf("%5d  %s   %s\n", tmp->id, tmp->time, tmp->command);
        else
            printf("%s\n", tmp->command);
        counter++;
        tmp = tmp->next;
    }
}

void show_no_param_history(history_t **history, int *status_flags)
{
    history_t *tmp = *history;
    history_t *last_node = *history;
    int counter = 0;

    while (tmp != NULL && counter < status_flags[3]) {
        last_node = tmp;
        counter++;
        tmp = tmp->next;
    }
    while (last_node != NULL) {
        printf("%s\n", last_node->command);
        last_node = last_node->prev;
    }
}

void show_history(history_t **history)
{
    history_t *tmp = *history;
    history_t *last_node = *history;

    while (tmp != NULL) {
        last_node = tmp;
        tmp = tmp->next;
    }
    while (last_node != NULL) {
        printf("%5d  %s   %s\n", last_node->id,
            last_node->time, last_node->command);
        last_node = last_node->prev;
    }
}

void show_history_num(int num, history_t **history)
{
    history_t *tmp = *history;
    history_t *last_node = *history;
    int counter = 0;

    while (tmp != NULL && counter < num) {
        last_node = tmp;
        counter++;
        tmp = tmp->next;
    }
    while (last_node != NULL) {
        printf("%5d  %s   %s\n", last_node->id,
            last_node->time, last_node->command);
        last_node = last_node->prev;
    }
}
