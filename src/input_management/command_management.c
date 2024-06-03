/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-nicolas.dumetz
** File description:
** command_management.c
*/

#include "minishell.h"

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

void display_command(char *line, history_t *tmp, int cursor_mv)
{
    printf("\033[2K\r");
    ttycheck();
    if (tmp != NULL)
        printf("%s", tmp->command);
    else
        printf("%s", line);
    for (int i = 0; i < cursor_mv; i++)
        printf("\033[D");
}
