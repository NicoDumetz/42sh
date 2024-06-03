/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-matisse.dufour
** File description:
** garbage_collector.c
*/

#include "minishell.h"

void free_collector(collector_t **collector)
{
    collector_t *node = NULL;
    collector_t *tmp = NULL;

    if (!collector)
        return;
    node = *collector;
    while (node) {
        tmp = node;
        node = node->next;
        free(tmp->data);
        free(tmp);
    }
    free(collector);
}

static collector_t **create_new_node(void *data, collector_t **collector)
{
    collector_t *new_node = NULL;

    new_node = malloc(sizeof(collector_t));
    if (new_node) {
        free(data);
        free_collector(collector);
        return NULL;
    }
    new_node->data = data;
    new_node->next = *collector;
    *collector = new_node;
    return collector;
}

void *gmalloc(size_t size)
{
    static collector_t **collector = NULL;
    void *data = NULL;

    if (!size) {
        free_collector(collector);
        return NULL;
    }
    data = malloc(size);
    if (!data) {
        free_collector(collector);
        return NULL;
    }
    collector = create_new_node(data, collector);
    if (!collector)
        return NULL;
    return data;
}
