/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-nicolas.dumetz
** File description:
** display_command.c
*/

#include "../../include/minishell.h"
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>

static void move_cursor(int cursor_up, struct winsize *w, int actual_cursor)
{
    if (cursor_up > 0) {
        for (int i = 0; i < cursor_up; i++)
            my_printf("\033[1A");
        my_printf("\r\033[%dC", w->ws_col);
    }
    for (int i = 0; i < actual_cursor; i++)
        my_printf("\033[1D");
}

static void down_cursor(getline_t *getmy, int actual_clear, char *command)
{
    for (int i = 0; i < (getmy->clear - actual_clear) + getmy->cursor_up; i++)
        my_printf("\033[1B");
    my_printf("\033[2K\r");
    for (int i = 1; i < getmy->clear; i++)
        my_printf("\033[1A\033[2K\r");
    ttycheck();
    my_printf("%s", command);
}

static void count_line_to_clear(getline_t *getmy, int rest, int *actual_clear)
{
    if (rest > 0)
        (*actual_clear)++;
    if (*actual_clear < getmy->previous_clear)
        my_printf("\033[%dA", getmy->previous_clear - *actual_clear);
    if (*actual_clear > getmy->previous_clear) {
        for (int i = 0; i < *actual_clear - getmy->previous_clear; i++)
            my_printf("\n");
    }
    if (*actual_clear > getmy->clear)
        getmy->clear = *actual_clear;
    getmy->previous_clear = *actual_clear;
}

static void display_command2(struct winsize *w, char *command, getline_t
    *getmy)
{
    int size_prompt = get_prompt_size();
    int len = my_strlen(command);
    int actual_clear = (len + size_prompt) / w->ws_col;
    int rest = (len + size_prompt) % w->ws_col;
    int cursor_up = 0;
    int actual_cursor = getmy->cursor;

    count_line_to_clear(getmy, rest, &actual_clear);
    if (actual_cursor > rest && rest != 0) {
        cursor_up++;
        actual_cursor -= rest + 1;
    }
    for (; actual_cursor > w->ws_col; actual_cursor -= w->ws_col)
        cursor_up++;
    getmy->rest = rest;
    down_cursor(getmy, actual_clear, command);
    move_cursor(cursor_up, w, actual_cursor);
    getmy->cursor_up = cursor_up;
}

void display_command(char *line, history_t *tmp, getline_t *getmy)
{
    struct winsize w;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    if (tmp != NULL)
        display_command2(&w, tmp->command, getmy);
    else
        display_command2(&w, line, getmy);
}
