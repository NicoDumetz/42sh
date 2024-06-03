/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-nicolas.dumetz
** File description:
** command_management.c
*/

#include "minishell.h"
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
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

void update_command(int ch, char **line, history_t *tmp, int cursor)
{
    int len_tmp;
    int len = my_strlen(*line);

    if (tmp != NULL) {
        len_tmp = my_strlen(tmp->command);
        tmp->command = realloc(tmp->command, (len_tmp + 2) * sizeof(char));
        if (tmp->command == NULL)
            return;
        insert_char(tmp->command, ch, len_tmp, len_tmp - cursor);
    } else
        insert_char(*line, ch, len, len - cursor);
}

int choose_command(char **line, history_t **tmp, int exit)
{
    if (exit == -1)
        return -1;
    if (*tmp != NULL) {
        free(*line);
        *line = my_strdup((*tmp)->command);
        free((*tmp)->command);
        tmp = NULL;
        return my_strlen(*line);
    }
    return exit;
}

static void move_cursor(int cursor, int cursor_up, struct winsize *w)
{
    if (cursor_up > 0) {
        for (int i = 0; i < cursor_up; i++)
            printf("\033[1A");
        printf("\r\033[%dC", w->ws_col);
    }
    for (int i = 0; i < cursor; i++)
        printf("\033[1D");
}

static void down_cursor(int clear, char *command)
{
    for (int i = 0; i < clear; i++)
        printf("\033[1B");
    printf("\033[2K\r");
    for (int i = 1; i < clear; i++)
        printf("\033[1A\033[2K\r");
    ttycheck();
    printf("%s", command);
}

static void display_command2(struct winsize *w, char *command, int cursor, int
    *clear)
{
    int len = my_strlen(command);
    int actual_clear = (len + 3) / w->ws_col;
    int rest = (len + 3) % w->ws_col;
    int cursor_up = 0;

    if (rest > 1)
        actual_clear++;
    if (actual_clear > *clear)
        *clear = actual_clear;
    if (cursor > rest) {
        cursor_up++;
        cursor -= rest + 1;
    }
    for (; cursor > w->ws_col; cursor -= w->ws_col)
        cursor_up++;
    down_cursor(*clear, command);
    move_cursor(cursor, cursor_up, w);
}

void display_command(char *line, history_t *tmp, int cursor_mv, int *clear)
{
    struct winsize w;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    if (tmp != NULL)
        display_command2(&w, tmp->command, cursor_mv, clear);
    else
        display_command2(&w, line, cursor_mv, clear);
}
