/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-nicolas.dumetz
** File description:
** input_management.c
*/

#include "stdio.h"
#include "minishell.h"

static int end_tmp(char **line, history_t *tmp, int cursor_mv, int *clear)
{
    int len = my_strlen(tmp->command);

    tmp->command = realloc(tmp->command, (len + 2) * sizeof(char));
    if (tmp->command == NULL)
        return -1;
    tmp->command[len] = '\n';
    tmp->command[len + 1] = '\0';
    display_command(*line, tmp, cursor_mv, clear);
    *clear = 1;
    return len + 1;
}

int is_end(char **line, history_t *tmp, int *cursor_mv, int *line_to_clear)
{
    int len;

    *cursor_mv = 0;
    if (tmp != NULL) {
        return end_tmp(line, tmp, *cursor_mv, line_to_clear);
    } else {
        len = my_strlen(*line);
        (*line)[len] = '\n';
        (*line)[len + 1] = '\0';
        display_command(*line, tmp, *cursor_mv, line_to_clear);
        *line_to_clear = 1;
        return len + 1;
    }
}

static void choose_del(char *str, int sp_key, int *cursor)
{
    int len = my_strlen(str);

    if (sp_key == KEY_SUPPR && *cursor != 0) {
        delete_char(str, len, len - *cursor);
        (*cursor)--;
    } else if (sp_key == KEY_BACKSPACE)
        delete_char(str, len, len - *cursor - 1);
}

int is_del(char **line, history_t *tmp, int *cursor, int sp_key)
{
    if (tmp != NULL)
        choose_del(tmp->command, sp_key, cursor);
    if (tmp == NULL)
        choose_del(*line, sp_key, cursor);
    return *cursor;
}

int arrow_right(int *cursor)
{
    if (*cursor > 0)
        (*cursor)--;
    return *cursor;
}

int arrow_left(history_t *tmp, char *line, int *cursor)
{
    if (tmp != NULL) {
        if (*cursor < my_strlen(tmp->command))
            (*cursor)++;
    } else if (*cursor < my_strlen(line))
        (*cursor)++;
    return *cursor;
}
