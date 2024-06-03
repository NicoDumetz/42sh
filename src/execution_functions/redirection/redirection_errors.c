/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell2-matisse.dufour
** File description:
** errors.c
*/
#include "my.h"
#include "minishell.h"
#include <unistd.h>

static int check_name(char *command, int *j)
{
    int i = 0;

    if (command[*j] == command[*j + 1])
        *j += 1;
    for (i = *j + 1; command[i] == ' '; i++);
    if (command[i] == '\0' || command[i] == '<' || command[i] == '>') {
        write(2, "Missing name for redirect.\n", 27);
        return 1;
    }
    return 0;
}

static int ambigous_redirection(char *str)
{
    write(2, "Ambiguous ", 10);
    write(2, str, my_strlen(str));
    write(2, " redirect.\n", 11);
    return 1;
}

int redirection_errors(char *command, char **pipes, int i)
{
    int in_redirection = 0;
    int out_redirection = 0;

    for (int j = 0; command[j]; j++) {
        if (command[j] != '<' && command[j] != '>')
            continue;
        if (check_name(command, &j))
            return 1;
        if (command[j] == '<' && (i != 0 ||
        (command[j] == '<' && in_redirection != 0)))
            return ambigous_redirection("input");
        if (command[j] == '>' && (pipes[i + 1] != 0 ||
        (command[j] == '>' && out_redirection != 0)))
            return ambigous_redirection("output");
        if (command[j] == '<')
            in_redirection += 1;
        if (command[j] == '>')
            out_redirection += 1;
    }
    return 0;
}
