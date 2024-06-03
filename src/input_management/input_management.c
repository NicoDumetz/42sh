/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-nicolas.dumetz
** File description:
** input_management.c
*/

#include "stdio.h"
#include "minishell.h"

int is_end(char **line, int len, history_t *tmp)
{
    int len_tmp;

    if (tmp != NULL) {
        len_tmp = my_strlen(tmp->command);
        tmp->command = realloc(tmp->command, (len_tmp + 2) * sizeof(char));
        if (tmp->command == NULL)
            return -1;
        tmp->command[len_tmp] = '\n';
        tmp->command[len_tmp + 1] = '\0';
        return len_tmp + 1;
    } else {
        (*line)[len] = '\n';
        (*line)[len + 1] = '\0';
        return len + 1;
    }
}

void is_del(char **line, int len, history_t *tmp)
{
    int len_tmp;

    if (tmp != NULL) {
        len_tmp = my_strlen(tmp->command);
        tmp->command[len_tmp - 1] = '\0';
        printf("\b \b");
    } else if (len > 0) {
        (*line)[len - 1] = '\0';
        printf("\b \b");
    }
}
