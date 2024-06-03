/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-nicolas.dumetz
** File description:
** history_command.c
*/

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

static int is_history_flags(char *arg)
{
    if (arg[0] != '-') {
        write(2, "history: Badly formed number.\n", 30);
        return 0;
    }
    if (arg[0] == '-' && my_strlen(arg) == 1)
        return 1;
    for (int i = 1; arg[i] != '\0'; i++) {
        if (arg[i] != 'c' && arg[i] != 'h' && arg[i] != 'r') {
            write(2, "Usage: history [-chr] [# number of events].\n", 44);
            return 0;
        }
    }
    return 1;
}

static int is_correct_command(char **command)
{
    for (int i = 1; command[i] != 0; i++) {
        if (my_str_isnum(command[i]) == 1)
            return 1;
        if (is_history_flags(command[i]) != 1)
            return 0;
    }
    return 1;
}

static void fetch_flags2(char *command, int *status_flags)
{
    if (my_strstr(command, "c") != NULL)
        status_flags[0] = 1;
    if (my_strstr(command, "h") != NULL)
        status_flags[1] = 1;
    if (my_strstr(command, "r") != NULL)
        status_flags[2] = 1;
}

static void fetch_flags(char **command, int *status_flags)
{
    status_flags[0] = 0;
    status_flags[1] = 0;
    status_flags[2] = 0;
    status_flags[3] = 100;
    for (int i = 1; command[i] != 0; i++) {
        if (my_str_isnum(command[i]) == 1)
            status_flags[3] = my_getnbr(command[i]);
        else
            fetch_flags2(command[i], status_flags);
    }
}

static void show_history_flags(char **command, history_t **history)
{
    int *status_flags = malloc(sizeof(int) * 4);

    if (status_flags == NULL)
        return;
    fetch_flags(command, status_flags);
    if (status_flags[0] == 1) {
        clear_history(history);
        return free(status_flags);
    }
    if (status_flags[2] == 1) {
        show_reverse_history(history, status_flags);
        return free(status_flags);
    }
    if (status_flags[1] == 1) {
        show_no_param_history(history, status_flags);
        return free(status_flags);
    }
    show_history_num(status_flags[3], history);
}

static int history_flags(char **command, history_t **history)
{
    if (is_correct_command(command) != 1)
        return 1;
    if (my_str_isnum(command[1]) == 1)
        show_history_num(my_getnbr(command[1]), history);
    else
        show_history_flags(command, history);
    return 0;
}

int history_command(char *str, char ***, garbage_t *garbage)
{
    char **command = my_str_to_array(str, " ");
    int i;
    int error = 0;

    for (i = 0; command[i]; i++);
    if (i == 1) {
        freeing(0, command);
        show_history(garbage->history);
        return 0;
    } else if (i <= 3) {
        error = history_flags(command, garbage->history);
        freeing(0, command);
        return error;
    } else {
        write(2, "history: Too many arguments.\n", 29);
        freeing(0, command);
        return 1;
    }
}
