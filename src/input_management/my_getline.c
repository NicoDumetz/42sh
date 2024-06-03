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

static int choose_command(char **line, history_t **tmp, int exit)
{
    if (exit == -1)
        return -1;
    if (*tmp != NULL) {
        free(*line);
        *line = strdup((*tmp)->command);
        free((*tmp)->command);
        tmp = NULL;
        return my_strlen(*line);
    }
    return exit;
}

static void display_command(char *line, history_t *tmp)
{
    printf("\033[2K\r");
    ttycheck();
    if (tmp != NULL)
        printf("%s", tmp->command);
    else
        printf("%s", line);
}

static void analyse_input(int key, char **line, history_t **tmp,
    history_t **hist)
{
    switch (key) {
        case KEY_UP:
            return history_up(tmp, hist);
        case KEY_DOWN:
            return history_down(tmp);
        case KEY_RIGHT:
            printf("Right arrow pressed\n");
            break;
        case KEY_LEFT:
            printf("Left arrow pressed\n");
            break;
        case KEY_TAB:
            printf("Tab pressed\n");
            break;
        default:
            break;
    }
}

static void update_command(int ch, char **line, history_t *tmp, int len)
{
    size_t len_tmp;

    if (tmp != NULL) {
        len_tmp = my_strlen(tmp->command);
        tmp->command = realloc(tmp->command, (len_tmp + 2) * sizeof(char));
        if (tmp->command == NULL)
            return;
        tmp->command[len_tmp] = (char) ch;
        tmp->command[len_tmp + 1] = '\0';
    } else {
        (*line)[len] = (char) ch;
        (*line)[len + 1] = '\0';
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

    if (ch == '\n')
        return is_end(line, len, *tmp);
    if (sp_key == 0)
        update_command(ch, line, *tmp, len);
    else if (sp_key == KEY_BACKSPACE)
        is_del(line, len, *tmp);
    else
        analyse_input(sp_key, line, tmp, hist);
    return 0;
}

static int manage_input(char **line, history_t **tmp, size_t *n, history_t
    **hist)
{
    int len = my_strlen(*line);

    if (len > *n - 1) {
        *n += 120;
        *line = realloc(*line, *n * sizeof(char));
        if (*line == NULL)
            return -1;
    }
    return use_input(line, tmp, len, hist);
}

int my_getline(char **line, size_t *n, history_t **hist)
{
    int exit;
    history_t *tmp = NULL;

    *n = 120;
    *line = malloc(*n * sizeof(char));
    if (*line == NULL)
        return -1;
    *line[0] = '\0';
    display_command(*line, tmp);
    while (1) {
        exit = manage_input(line, &tmp, n, hist);
        display_command(*line, tmp);
        if (exit != 0)
            break;
    }
    return choose_command(line, &tmp, exit);
}
