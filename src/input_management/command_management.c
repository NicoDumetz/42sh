/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-nicolas.dumetz
** File description:
** command_management.c
*/

#include "minishell.h"
#include <string.h>

void delete_char(char *line, int len, int index)
{
    if (index < 0 || index >= len)
        return;
    for (int i = index; i < len; i++)
        line[i] = line[i + 1];
    line[len - 1] = '\0';
}

void insert_char(char *line, int ch, int len, int index)
{
    for (int i = len; i >= index; i--)
        line[i + 1] = line[i];
    line[index] = (char) ch;
    line[len + 1] = '\0';
}

void update_command(int ch, char **line, history_t *tmp, getline_t *getmy)
{
    if (tmp != NULL) {
        tmp->command = realloc(tmp->command,
            (getmy->len_tmp + 2) * sizeof(char));
        if (tmp->command == NULL)
            return;
        insert_char(tmp->command, ch, getmy->len_tmp, getmy->len_tmp -
            getmy->cursor);
    } else
        insert_char(*line, ch, getmy->len_line,
            getmy->len_line - getmy->cursor);
}

int choose_command(char **line, history_t **tmp, int exit)
{
    if (exit == -1)
        return -1;
    if (*tmp != NULL) {
        *line = my_strdup((*tmp)->command);
        free((*tmp)->command);
        tmp = NULL;
        return my_strlen(*line);
    }
    return exit;
}
