/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42-matisse.dufour
** File description:
** assemble_simple.c.c
*/

#include "minishell.h"

void assemble_hard(token_t **current, token_t **head)
{
    assemble_simple(*current, head);
    if ((*current)->next && (*current)->next->sep == ']') {
        *current = (*current)->next;
        assemble_simple(*current, head);
    }
}
