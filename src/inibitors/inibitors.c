/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-nicolas.dumetz
** File description:
** inibitors.c
*/

#include "minishell.h"
#include <unistd.h>

int get_string(token_t **head)
{
    token_t *current = (*head)->next;
    int len = 0;

    for (; current && current->sep != '\"'; current = current->next);
    if (current == NULL) {
        write(2, "Unmatched '\"'.\n", 15);
        return 1;
    }
    for (current = (*head)->next; current->sep != '\"';
    current = current->next)
        len += (current->sep == 0) ? strlen(current->arg) : 1;
    return 0;
}
