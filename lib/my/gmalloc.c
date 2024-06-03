/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-matisse.dufour
** File description:
** garbage_collector.c
*/

#include "my.h"

static collector_t *free_collector(collector_t *collector)
{
    collector_t *tmp = NULL;

    if (!collector)
        return NULL;
    while (collector) {
        tmp = collector;
        collector = collector->next;
        free(tmp->data);
        free(tmp);
        tmp = NULL;
    }
    collector = NULL;
    return NULL;
}

static collector_t *create_new_node(size_t size)
{
    collector_t *new_node = NULL;
    void *data = malloc(size);

    if (!data)
        return NULL;
    data = memset(data, 0, size);
    new_node = malloc(sizeof(collector_t));
    if (!new_node) {
        free(data);
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void *gmalloc(size_t size)
{
    static collector_t *collector = NULL;
    collector_t *new_node = NULL;

    if (!size) {
        collector = free_collector(collector);
        return NULL;
    }
    new_node = create_new_node(size);
    if (!new_node) {
        free_collector(collector);
        exit(84);
    }
    if (!collector)
        new_node->next = NULL;
    else
        new_node->next = collector;
    collector = new_node;
    return collector->data;
}
