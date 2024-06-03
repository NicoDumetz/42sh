/*
** EPITECH PROJECT, 2024
** cleanup garbage
** File description:
** cleanuo
*/

#include "minishell.h"
#include "my.h"
#include <unistd.h>

void cleanup(garbage_t *g)
{
    free_alias(g);
    free_var(g);
    free_history(g->history);
}
