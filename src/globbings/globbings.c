/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42-matisse.dufour
** File description:
** fork.c
*/

#include "minishell.h"

char **make_globbings(char *str)
{
    glob_t glob_result;
    int len = 0;
    char **arr = 0;

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

static token_t *create_new_node(char *arg)
{
    token_t *new_node = malloc(sizeof(token_t));

    new_node->sep = '\0';
    new_node->arg = arg;
    new_node->next = NULL;
    new_node->prev = NULL;
    new_node->index = 0;
    return (new_node);
}

static void connect_new_list(
    token_t *prev, token_t **actual, token_t **start, token_t *new_list)
{
    if (prev)
        prev->next = (*actual)->next;
    new_list->prev = (*actual)->prev;
    if ((*actual)->next)
        (*actual)->next->prev = prev;
    if ((*actual)->prev)
        (*actual)->prev->next = new_list;
    else
        *start = new_list;
    free_token(*actual);
    *actual = prev;
}

static void create_new_arg(token_t **actual, token_t **start, char **new_arg)
{
    token_t *new_list = NULL;
    token_t *prev = NULL;
    token_t *new_node = NULL;

    for (int i = 0; new_arg[i] != NULL; i++) {
        new_node = create_new_node(new_arg[i]);
        if (new_list == NULL)
            new_list = new_node;
        else {
            new_node->prev = prev;
            prev->next = new_node;
        }
        prev = new_node;
    }
    connect_new_list(prev, actual, start, new_list);
}

static void correct_index(token_t *head, int index)
{
    for (token_t *act = head; act; act = act->next) {
        act->index = index;
        index++;
    }
}

void supp_token_glob(token_t **token, token_t **start)
{
    token_t *to_delete = *token;
    token_t *next = to_delete->next;
    token_t *prev = to_delete->prev;

    if (prev == NULL) {
        *start = next;
        (*start)->prev = NULL;
        free_token(to_delete);
        *token = next;
        return;
    }
    if (next != NULL)
        next->prev = prev;
    prev->next = next;
    free_token(to_delete);
    *token = next;
}

static int check_glob(token_t **token, token_t **start, int *check)
{
    char **new_arg = make_globbings((*token)->arg);
    static int count = 0;

    if (new_arg != NULL)
        *check = 1;
    else if (*check == 0) {
        supp_token_glob(token, start);
        *check = -1;
    } else {
        supp_token_glob(token, start);
        *check = 0;
    }
    if (count == 0)
        count = tab_len(new_arg);
    if (*check == 1) {
        create_new_arg(token, start, new_arg);
        free(new_arg);
    }
    return (count);
}

int switch_sep_globbings(token_t **current, token_t **start)
{
    if ((*current)->sep == '*' || (*current)->sep == '?') {
        assemble_simple(*current, start);
        if (((*current)->next && (*current)->next->sep == '*') ||
            ((*current)->next && (*current)->next->sep == '?') ||
            ((*current)->next && (*current)->next->sep == '[')) {
            return 0;
        }
        return 1;
    }
    if ((*current)->sep == '[' && assemble_hard(current, start) == 1) {
        if (((*current)->next && (*current)->next->sep == '*') ||
            ((*current)->next && (*current)->next->sep == '?') ||
            ((*current)->next && (*current)->next->sep == '[')) {
                return 0;
            }
        return 1;
    }
    return -1;
}

int rebuild_token(token_t *current, token_t **start)
{
    int count = 0;
    int check = 0;
    int which = 0;

    while (current) {
        which = switch_sep_globbings(&current, start);
        if (which == 1)
            count = check_glob(&current, start, &check);
        if (check < 1 && which == 1)
            continue;
        if (current->sep == ']')
            assemble_simple(current, start);
        if (current && current->next) {
            current = current->next;
        } else
            break;
    }
    if (check == -1)
        count = -1;
    return count;
}

int globbings(garbage_t *, token_t **start)
{
    int save_index = (*start)->index;
    int count = 0;

    count = rebuild_token(*start, start);
    correct_index(*start, save_index);
    if (count == -1) {
        fprintf(stderr, "glob: No match.\n");
        free_token_list(start);
        start = NULL;
    }
    return count;
}
