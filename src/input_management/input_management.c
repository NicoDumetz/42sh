/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-nicolas.dumetz
** File description:
** input_management.c
*/

#include "stdio.h"
#include "minishell.h"

static int end_tmp(char **line, history_t *tmp, getline_t *getmy)
{
    tmp->command = realloc(tmp->command, (getmy->len_tmp + 2) * sizeof(char));
    if (tmp->command == NULL)
        return -1;
    tmp->command[getmy->len_tmp] = '\n';
    tmp->command[getmy->len_tmp + 1] = '\0';
    display_command(*line, tmp, getmy);
    return getmy->len_tmp + 1;
}

int is_end(char **line, history_t *tmp, getline_t *getmy)
{
    if (tmp != NULL) {
        return end_tmp(line, tmp, getmy);
    } else {
        (*line)[getmy->len_line] = '\n';
        (*line)[getmy->len_line + 1] = '\0';
        display_command(*line, tmp, getmy);
        return getmy->len_line + 1;
    }
}

static void choose_del(char *str, getline_t *getmy)
{
    int len = my_strlen(str);

    if (getmy->key == KEY_SUPPR && getmy->cursor != 0) {
        delete_char(str, len, len - getmy->cursor);
        getmy->cursor--;
    } else if (getmy->key == KEY_BACKSPACE)
        delete_char(str, len, len - getmy->cursor - 1);
}

void is_del(char **line, history_t *tmp, getline_t *getmy)
{
    if (tmp != NULL)
        choose_del(tmp->command, getmy);
    if (tmp == NULL)
        choose_del(*line, getmy);
}

void arrow_right(getline_t *getmy)
{
    if (getmy->cursor > 0)
        getmy->cursor--;
}

void arrow_left(history_t *tmp, char *line, getline_t *getmy)
{
    if (tmp != NULL) {
        if (getmy->cursor < getmy->len_tmp)
            getmy->cursor++;
    } else if (getmy->cursor < my_strlen(line))
        getmy->cursor++;
}
