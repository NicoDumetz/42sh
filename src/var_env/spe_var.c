/*
** EPITECH PROJECT, 2024
** spe var
** File description:
** spe var
*/

#include "my.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


int check_spe_var(token_t *token, pipeline_t *pipeline, garbage_t *garbage)
{
    token_t *next;

    if ((strcmp(token->arg, "$") == 0 || strcmp(token->arg, "\"$") == 0) &&
        token->next->sep == '?') {
        token->next->prev = token;
        next = token->next;
        token->next = next->next;
        free_token(&next);
        insert_node(token, int_to_str(garbage->return_value), 1, pipeline);
        return 1;
    }
    return 0;
}
