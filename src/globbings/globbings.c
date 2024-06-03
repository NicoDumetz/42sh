/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42-matisse.dufour
** File description:
** fork.c
*/

#include "minishell.h"

char **make_globbings(char *str)
{
    glob_t glob_result;
    int len = 0;
    char **arr = 0;

    glob(str, GLOB_NOCHECK, NULL, &glob_result);
    for (; glob_result.gl_pathv[len] != NULL; len++);
    arr = malloc(sizeof(char *) * (len + 1));
    for (int i = 0; i < len; i++)
        arr[i] = strdup(glob_result.gl_pathv[i]);
    arr[len] = NULL;
    globfree(&glob_result);
    return arr;
}

static token_t *create_new_node(char *arg)
{
    token_t *new_node = malloc(sizeof(token_t));

    new_node->sep = '\0';
    new_node->arg = arg;
    new_node->next = NULL;
    new_node->prev = NULL;
    new_node->index = 0;
    return (new_node);
}

static void connect_new_list(
    token_t *prev, token_t **actual, token_t **start, token_t *new_list)
{
    if (prev)
        prev->next = (*actual)->next;
    new_list->prev = (*actual)->prev;
    if ((*actual)->next)
        (*actual)->next->prev = prev;
    if ((*actual)->prev)
        (*actual)->prev->next = new_list;
    else
        *start = new_list;
    free_token(*actual);
    *actual = prev;
}

void create_new_arg(token_t **actual, token_t **start, char **new_arg)
{
    token_t *new_list = NULL;
    token_t *prev = NULL;
    token_t *new_node = NULL;

    for (int i = 0; new_arg[i] != NULL; i++) {
        new_node = create_new_node(new_arg[i]);
        if (new_list == NULL)
            new_list = new_node;
        else {
            new_node->prev = prev;
            prev->next = new_node;
        }
        prev = new_node;
    }
    connect_new_list(prev, actual, start, new_list);
}

int rebuild_token(token_t *current, token_t **start, int index)
{
    while (current && current->index <= index) {
        if (current->sep == '*' || current->sep == '?')
            assemble_simple(current, start);
        current = current->next;
    }
    return 0;
}

void correct_index(token_t *head, int index)
{
    for (token_t *act = head; act; act = act->next) {
        act->index = index;
        index++;
    }
}

static int check_glob(token_t **token, token_t **start)
{
    char **new_arg = make_globbings((*token)->arg);

    create_new_arg(token, start, new_arg);
    free(new_arg);
    return (0);
}

int globbings(token_t **start, int index)
{
    int save_index = (*start)->index;
    token_t *next = NULL;
    token_t *current = *start;

    rebuild_token(*start, start, index);
    current = *start;
    while (current && current->index <= index) {
        next = current->next;
        if (current->arg)
            check_glob(&current, start);
        current = next;
    }
    correct_index(*start, save_index);
    return 0;
}
