/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell2-matisse.dufour
** File description:
** errors.c
*/
#include "my.h"
#include "minishell.h"
#include <unistd.h>

static void add_line_to_result(char **result, char *line)
{
    int len = my_strlen(*result) + my_strlen(line);
    char *buffer = gmalloc(sizeof(char) * (len + 1));
    int k = 0;

    my_putstr("> ");
    if (*result) {
        for (int i = 0; (*result)[i]; i++) {
            buffer[i] = (*result)[i];
            k++;
        }
    }
    for (int j = 0; line[j]; j++) {
        buffer[k] = line[j];
        k++;
    }
    buffer[k] = '\0';
    *result = buffer;
}

int getline_loop(char *line, int fd[2], char *file, char **result)
{
    line[my_strlen(line) - 1] = '\0';
    if (my_strcmp(file, line) == 0) {
        write(fd[1], *result, my_strlen(*result));
        close(fd[1]);
        return (1);
    }
    line[my_strlen(line)] = '\n';
    add_line_to_result(result, line);
    return (0);
}

int find_stdin(char *file)
{
    char *line = NULL;
    size_t size = 0;
    char *result = NULL;
    int fd[2];

    pipe(fd);
    my_putstr("> ");
    set_canonical_mode();
    while (getline(&line, &size, stdin) != -1) {
        if (getline_loop(line, fd, file, &result) != 0) {
            set_non_canonical_mode();
            return (fd[0]);
        }
        line = NULL;
        size = 0;
    }
    set_canonical_mode();
    return (-1);
}
