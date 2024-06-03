/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42-matisse.dufour
** File description:
** assemble_simple.c.c
*/

#include "minishell.h"

int find_len_new_arg_simple(token_t *current)
{
    int count = 1;

    if (current->prev && current->prev->arg)
        count += my_strlen(current->prev->arg);
    if (current->next && current->next->arg)
        count += my_strlen(current->next->arg);
    return (count);
}

int supp_garbage(token_t *token, char *true_arg, token_t **head)
{
    token_t *tmp = NULL;

    token->sep = '\0';
    token->arg = true_arg;
    if (token->prev && token->prev->arg) {
        tmp = token->prev;
        token->prev = token->prev->prev;
        if (token->prev)
            token->prev->next = token;
        else
            *head = token;
        free_token(tmp);
    }
    if (token->next && token->next->arg) {
        tmp = token->next;
        token->next = token->next->next;
        if (token->next)
            token->next->prev = token;
        free_token(tmp);
    }
}

int assemble_simple(token_t *current, token_t **head)
{
    char *true_arg = NULL;
    int len = find_len_new_arg_simple(current);
    int i = 0;

    true_arg = malloc(sizeof(char) * (len + 1));
    if (current->prev && current->prev->arg)
        for (i = 0; current->prev->arg[i]; i++)
            true_arg[i] = current->prev->arg[i];
    true_arg[i] = current->sep;
    i++;
    if (current->next && current->next->arg)
        for (int j = 0; current->next->arg[j]; j++) {
            true_arg[i] = current->next->arg[j];
            i++;
        }
    true_arg[i] = '\0';
    supp_garbage(current, true_arg, head);
}
