/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-nicolas.dumetz
** File description:
** add_history.c
*/

#include "minishell.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

static void get_time(history_t *node)
{
    time_t current_time;
    struct tm *time_info;

    node->time = malloc(sizeof(char) * 9);
    if (node->time == NULL)
        return;
    time(&current_time);
    time_info = localtime(&current_time);
    if (time_info == NULL) {
        free(node->time);
        node->time = NULL;
        return;
    }
    strftime(node->time, 9, "%H:%M:%S", time_info);
}

static void add_node_history(char *command, history_t **history)
{
    history_t *new = malloc(sizeof(history_t));
    static int id = 1;

    if (new == NULL)
        return;
    new->id = id;
    id++;
    get_time(new);
    new->command = my_strdup(command);
    new->prev = NULL;
    new->next = *history;
    if (*history != NULL)
        (*history)->prev = new;
    *history = new;
}

static void del_node_history(history_t *node, history_t **history)
{
    if (node == NULL)
        return;
    if (node->prev != NULL && node->next != NULL) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    if (node->prev != NULL && node->next == NULL)
        node->prev->next = NULL;
    if (node->next != NULL && node->prev == NULL) {
        node->next->prev = NULL;
        *history = node->next;
    }
    if (node->next == NULL && node->prev == NULL)
        *history = NULL;
    free(node->time);
    free(node->command);
    free(node);
}

static void search_same_command(char *command, history_t **history)
{
    history_t *tmp = *history;

    while (tmp != NULL) {
        if (my_strcmp(tmp->command, command) == 0 &&
            my_strlen(tmp->command) == my_strlen(command)) {
            del_node_history(tmp, history);
            return;
        }
        tmp = tmp->next;
    }
}

static void free_excess_node(history_t **history)
{
    history_t *tmp = *history;
    history_t *last_node = NULL;
    int counter = 0;

    while (tmp != NULL) {
        counter++;
        last_node = tmp;
        tmp = tmp->next;
    }
    if (counter >= 100)
        del_node_history(last_node, history);
}

static void format_command(char *command, char **pretty_command)
{
    char **command_tab = my_str_to_minishell_array(command, " \n\t");
    int count_letter = 0;
    int i;

    for (i = 0; command_tab[i]; i++)
        count_letter += my_strlen(command_tab[i]);
    *pretty_command = malloc(sizeof(char) * (count_letter + i + 1));
    if (*pretty_command == NULL)
        return;
    (*pretty_command)[0] = '\0';
    for (i = 0; command_tab[i] != 0; i++) {
        strcat(*pretty_command, command_tab[i]);
        if (command_tab[i + 1] != NULL)
            strcat(*pretty_command, " ");
        free(command_tab[i]);
    }
    if (my_strlen(*pretty_command) == 0)
        return;
    free(command_tab);
}

void add_history(char **command, history_t **history)
{
    char *pretty_command = NULL;

    format_command(*command, &pretty_command);
    if (pretty_command == NULL || my_strlen(pretty_command) == 0)
        return;
    search_same_command(pretty_command, history);
    free_excess_node(history);
    add_node_history(pretty_command, history);
    *command = my_strdup(pretty_command);
}
