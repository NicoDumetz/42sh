/*
** EPITECH PROJECT, 2024
** manage
** File description:
** manage
*/

#include "my.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

// garbage_t init_local(garbage_t *garbage)
// {
//     char *cwd = getcwd(NULL, 0);

//     set_local("term", getenv("TERM"), garbage);
//     if (cwd != NULL) {
//         set_local("cwd", cwd, garbage);
//     } else
//         set_local("cwd", "", garbage);
// }

static int del_var(char *name, garbage_t *garbage)
{
    var_t *current = garbage->local;
    var_t *prev = NULL;

    for (; current != NULL; current = current->next) {
        if (strcmp(name, current->var) == 0) {
            delete_var(current, prev, garbage);
            return 1;
        }
        prev = current;
    }
    return 1;
}

int var_len(garbage_t *garbage)
{
    var_t *current = garbage->local;
    int compt = 0;
    var_t *prev = NULL;
    var_t *next;

    if (garbage == NULL || current == NULL)
        return 0;
    for (; current; current = current->next) {
        compt++;
        if (compt > 1000)
            del_var(current->var, garbage);
        prev = current;
    }
    return compt;
}

token_t *insert_node(token_t *token, char *com, garbage_t *garbage)
{
    char temp[my_strlen(com) + 2];
    token_t **insert;
    token_t *current;

    my_strcpy(temp, com);
    temp[my_strlen(com)] = '\n';
    temp[my_strlen(com) + 1] = '\0';
    insert = init_token_list(temp);
    if (token->prev != NULL)
        token->prev->next = *insert;
    else
        garbage->token_list = insert;
    current = *insert;
    for (; current->next->next; current = current->next);
    current->next = token->next;
    token->next->prev = current;
    token = *insert;
    reset_index(garbage);
    return token;
}
