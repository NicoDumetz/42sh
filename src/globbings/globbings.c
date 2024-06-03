/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42-matisse.dufour
** File description:
** fork.c
*/

#include "minishell.h"

char **make_globbings(token_t *token)
{
    glob_t glob_result;
    int error = 0;
    int len = 0;
    char **arr = 0;

    if (token->sep == ' ' || token->sep == '\n')
        glob(" ", GLOB_NOCHECK, NULL, &glob_result);
    if (token->arg)
        glob(token->arg, GLOB_NOCHECK, NULL, &glob_result);
    if (glob(str, 0, NULL, &glob_result) == GLOB_NOMATCH)
        return NULL;
    for (; glob_result.gl_pathv[len] != NULL; len++);
    arr = malloc(sizeof(char *) * (len + 1));
    for (int i = 0; i < len; i++)
        arr[i] = strdup(glob_result.gl_pathv[i]);
    arr[len] = NULL;
    globfree(&glob_result);
    return arr;
}

token_t *create_new_arg(token_t *head, char **new_arg)
{
    token_t *new_list = NULL;
    token_t *current = NULL;
    token_t *new_node = NULL;

    for (int i = 0; new_arg[i] != NULL; i++) {
        new_node = malloc(sizeof(token_t));
        new_node->arg = new_arg[i];
        new_node->next = NULL;
        if (new_list == NULL) {
            new_list = new_node;
            current = new_node;
        } else {
            current->next = new_node;
            current = current->next;
        }
    }
    current->next = head->next;
    head->prev->next = new_list;
    free(head);
    return new_list;
}

int globbings_function(garbage_t *garbage, token_t **token_list)
{
    token_t *head = *token_list;
    token_t *prev = NULL;
    token_t *current = NULL;
    char **new_arg = NULL;

    lexing_features(garbage, token_list);
    if (garbage->return_value < 0)
        return -1;
    new_arg = make_globbings(head->next);
    if (new_arg) {
        *token_list = create_new_arg(head, new_arg);
        free(new_arg);
    }
    return 0;
}
