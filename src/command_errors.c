/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell2-matisse.dufour
** File description:
** command_errors.c
*/
#include "minishell.h"
#include "my.h"
#include <unistd.h>

static int null_command(char **, int save_in, int save_out)
{
    close(save_in);
    close(save_out);
    write(2, "Invalid null command.\n", 22);
    return 1;
}

static void pass_redirection(char *str, int *i)
{
    for (; str[*i] && (str[*i] == '<' || str[*i] == '>' || str[*i] == ' ');
    *i += 1);
    for (; str[*i] && str[*i] != ' '; *i += 1);
    if (str[*i] == '<' || str[*i] == '>')
        pass_redirection(str, i);
}

static int check_null_command(char *str)
{
    for (int i = 0; str[i]; i++) {
        if (str[i] == '<' || str[i] == '>')
            pass_redirection(str, &i);
        if (str[i] == '\0')
            break;
        if (str[i] != ' ')
            return 0;
    }
    return 1;
}

int command_errors(char *str, char **pipes, int save_in, int save_out)
{
    if (str[0] == '|')
        return null_command(pipes, save_in, save_out);
    for (int i = 0; pipes[i]; i++) {
        if (redirection_errors(pipes[i], pipes, i)) {
            close(save_in);
            close(save_out);
            return 1;
        }
    if (check_null_command(str))
        return null_command(pipes, save_in, save_out);
    }
    if (str[my_strlen(str) - 1] == '|')
        return null_command(pipes, save_in, save_out);
    return 0;
}
