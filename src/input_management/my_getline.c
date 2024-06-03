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

static void analyse_input(getline_t *getmy, char **line, history_t **tmp,
    history_t **hist)
{
    switch (getmy->key) {
        case KEY_UP:
            return history_up(tmp, hist, getmy);
        case KEY_DOWN:
            return history_down(tmp, getmy);
        case KEY_RIGHT:
            return arrow_right(getmy);
        case KEY_LEFT:
            return arrow_left(*tmp, *line, getmy);
        case KEY_BACKSPACE:
        case KEY_SUPPR:
            return is_del(line, *tmp, getmy);
        case KEY_TAB:
            return is_tab(line, *tmp, getmy);
        default:
            break;
    }
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

static int ctrl_d(void)
{
    my_printf("exit\n");
    return -1;
}

static int use_input(char **line, history_t **tmp, history_t **hist,
    getline_t *getmy)
{
    getmy->ch = getchar();
    getmy->key = get_id_key(getmy->ch);
    if (getmy->ch == 4)
        return ctrl_d();
    if (getmy->ch == '\n')
        return is_end(line, *tmp, getmy);
    if (getmy->key == 0)
        update_command(getmy->ch, line, *tmp, getmy);
    else
        analyse_input(getmy, line, tmp, hist);
    display_command(*line, *tmp, getmy);
    return 0;
}

static int manage_input(char **line, history_t **tmp, getline_t *getmy,
    history_t **hist)
{
    getmy->len_line = my_strlen(*line);
    if (*tmp != NULL)
        getmy->len_tmp = my_strlen((*tmp)->command);
    if (getmy->len_line > (int) getmy->n - 2) {
        getmy->n += 120;
        *line = realloc(*line, getmy->n * sizeof(char));
        if (*line == NULL)
            return -1;
    }
    return use_input(line, tmp, hist, getmy);
}

static getline_t *init_getline(getline_t *getmy)
{
    getmy->n = 120;
    getmy->len_line = 0;
    getmy->len_tmp = 0;
    getmy->cursor = 0;
    getmy->cursor_up = 0;
    getmy->clear = 1;
    getmy->previous_clear = 1;
    getmy->tab = -1;
    getmy->word = NULL;
    return getmy;
}

int my_getline_interact(char **line, history_t **hist)
{
    int exit;
    history_t *tmp = NULL;
    getline_t *getmy = malloc(sizeof(getline_t));

    if (getmy == NULL)
        return -1;
    init_getline(getmy);
    *line = malloc(getmy->n * sizeof(char));
    if (*line == NULL)
        return -1;
    *line[0] = '\0';
    display_command(*line, tmp, getmy);
    while (1) {
        exit = manage_input(line, &tmp, getmy, hist);
        if (exit != 0)
            break;
    }
    free(getmy);
    return choose_command(line, &tmp, exit);
}

int my_getline(char **line, size_t *n, history_t **hist, FILE *stream)
{
    if (isatty(0) == 1)
        return my_getline_interact(line, hist);
    else
        return (int) getline(line, n, stream);
}
