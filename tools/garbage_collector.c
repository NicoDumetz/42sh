/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-matisse.dufour
** File description:
** garbage_collector.c
*/

#include "minishell.h"

static collector_t **free_collector(collector_t **collector)
{
    collector_t *node = NULL;
    collector_t *tmp = NULL;

    if (!collector)
        return collector;
    node = *collector;
    while (node) {
        tmp = node;
        node = node->next;
        free(tmp->data);
        free(tmp);
    }
    free(collector);
    collector = NULL;
    return NULL;
}

static collector_t **create_new_node(void *data, collector_t **collector)
{
    collector_t *new_node = NULL;

    new_node = malloc(sizeof(collector_t));
    if (new_node) {
        free(data);
        collector = free_collector(collector);
        exit(84);
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
        collector = free_collector(collector);
        return NULL;
    }
    data = malloc(size);
    if (!data) {
        collector = free_collector(collector);
        exit(84);
    }
    collector = create_new_node(data, collector);
    if (!collector)
        exit(84);
    return data;
}
