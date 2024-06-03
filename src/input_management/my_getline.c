/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-nicolas.dumetz
** File description:
** my_getline.c
*/

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int analyse_input(int key, char **line, history_t **tmp,
    history_t **hist)
{
    static int cursor = 0;

    switch (key) {
        case KEY_UP:
            return history_up(tmp, hist, &cursor);
        case KEY_DOWN:
            return history_down(tmp, &cursor);
        case KEY_RIGHT:
            return arrow_right(&cursor);
        case KEY_LEFT:
            return arrow_left(*tmp, *line, &cursor);
        case KEY_BACKSPACE:
        case KEY_SUPPR:
            return is_del(line, *tmp, &cursor, key);
        default:
            break;
    }
    return cursor;
}

static int is_arrow(void)
{
    getchar();
    switch (getchar()) {
        case 'A':
            return 1;
        case 'B':
            return 2;
        case 'C':
            return 3;
        case 'D':
            return 4;
        case '3':
            if (getchar() == '~')
                return 7;
            return 0;
        default:
            return 0;
    }
}

static int get_id_key(int c)
{
    if (c == 27)
        return is_arrow();
    else if (c == '\t')
        return 5;
    if (c == 127)
        return 6;
    return 0;
}

static int use_input(char **line, history_t **tmp, int len, history_t **hist)
{
    int ch = getchar();
    int sp_key = get_id_key(ch);
    static int cursor_mv = 0;
    static int line_to_clear = 1;

    if (ch == 4) {
        cursor_mv = 0;
        return -1;
    }
    if (ch == '\n')
        return is_end(line, *tmp, &cursor_mv, &line_to_clear);
    if (sp_key == 0)
        update_command(ch, line, *tmp, cursor_mv);
    else
        cursor_mv = analyse_input(sp_key, line, tmp, hist);
    display_command(*line, *tmp, cursor_mv, &line_to_clear);
    return 0;
}

static int manage_input(char **line, history_t **tmp, size_t *n, history_t
    **hist)
{
    int len = my_strlen(*line);

    if (len > *n - 2) {
        *n += 120;
        *line = realloc(*line, *n * sizeof(char));
        if (*line == NULL)
            return -1;
    }
    return use_input(line, tmp, len, hist);
}

int my_getline_interact(char **line, size_t *n, history_t **hist)
{
    int exit;
    history_t *tmp = NULL;
    int clear = 1;

    *n = 120;
    *line = malloc(*n * sizeof(char));
    if (*line == NULL)
        return -1;
    *line[0] = '\0';
    display_command(*line, tmp, 0, &clear);
    while (1) {
        exit = manage_input(line, &tmp, n, hist);
        if (exit != 0)
            break;
    }
    return choose_command(line, &tmp, exit);
}

int my_getline(char **line, size_t *n, history_t **hist, FILE *stream)
{
    if (isatty(0) == 1)
        return my_getline_interact(line, n, hist);
    else
        return (int) getline(line, n, stream);
}
