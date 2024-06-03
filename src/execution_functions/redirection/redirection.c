/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell2-matisse.dufour
** File description:
** redirection.c
*/
#include "minishell.h"
#include "my.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void write_error(char *name)
{
    char *error = strerror(errno);

    if (error == 0) {
        free(name);
        return;
    }
    write(2, name, my_strlen(name));
    write(2, ": ", 2);
    write(2, error, my_strlen(error));
    write(2, ".\n", 2);
    free(name);
}

static char *get_name(char *str, int j, int i)
{
    char *name;
    int size;

    for (; str[j] && str[j] == ' '; j++);
    for (size = 0; str[j + size] && str[j + size] != ' ' &&
    str[j + size] != '<' && str[j + size] != '>'; size++);
    if (size == 0)
        return 0;
    name = malloc(size + 1);
    my_strncpy(name, str + j, size);
    my_strcpy(str + i, str + j + size);
    return name;
}

static void close_fd(int fd_in, int fd_out)
{
    if (fd_in > -1)
        close(fd_in);
    if (fd_out > -1)
        close(fd_out);
}

static void set_fd_out(char *str, int *i, pipeline_t *node)
{
    int mode = (str[*i + 1] != '>') ? (O_CREAT | O_WRONLY | O_TRUNC) :
    (O_CREAT | O_WRONLY | O_APPEND);
    int j = (str[*i + 1] == '>') ? *i + 2 : *i + 1;
    char *name;

    name = get_name(str, j, *i);
    if (name == 0) {
        node->output = -1;
        return;
    }
    node->output = open(name, mode, 0644);
    *i -= 1;
    if (node->output == -1)
        return write_error(name);
    dup2(node->output, STDOUT_FILENO);
    close(node->output);
    free(name);
}

static void prompt(int save_out)
{
    if (isatty(STDIN_FILENO))
        write(save_out, "? ", 2);
}

static void redirect_input(char **line, char *end, int save_out)
{
    int pipefd[2];
    size_t len = 0;

    pipe(pipefd);
    prompt(save_out);
    while (getline(line, &len, stdin) != -1 && my_strcmp(*line, end) != 0) {
        write(pipefd[1], *line, my_strlen(*line));
        prompt(save_out);
    }
    close(pipefd[1]);
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[0]);
}

static void set_input(char *str, int *i, int save_out)
{
    char *line = get_name(str, *i + 2, *i);
    char *end = malloc(my_strlen(line) + 2);

    my_strcpy(end, line);
    my_strcat(end, "\n");
    free(line);
    redirect_input(&line, end, save_out);
    free(line);
    free(end);
    *i += 1;
}

static void set_fd_in(char *str, int *i, int *fd_in, int save_out)
{
    char *name;

    if (str[*i + 1] == '<')
        return set_input(str, i, save_out);
    name = get_name(str, *i + 1, *i);
    if (name == 0) {
        *fd_in = -1;
        return;
    }
    *fd_in = open(name, O_RDONLY);
    if (*fd_in == -1)
        return write_error(name);
    dup2(*fd_in, STDIN_FILENO);
    close(*fd_in);
    free(name);
}

static int find_next_sep(token_t *token)
{
    for (; token; token = token->next) {
        if (token->sep && token->sep != ' ')
            return token->index;
    }
    return -1;
}

pipeline_t *execute_redirection(garbage_t *garbage, pipeline_t *pipeline)
{
    int result;
    int fd_in = -2;
    int fd_out = -2;
    char *str = NULL;

    str = token_to_str(*pipeline->next->token_list);
    for (int i = 0; str[i]; i++) {
        if (str[i] == '<') {
            set_fd_in(str, &i, &fd_in, pipeline->input);
            continue;
        }
        if (str[i] == '>')
            set_fd_out(str, &i, pipeline);
    }
    free(str);
    if (fd_out == -1 || fd_in == -1)
        return pipeline->next;
    // format_str(str);
    garbage->return_value = new_process(pipeline, token_to_str_array(*pipeline->token_list,
        get_token_list_size(*pipeline->token_list)), *garbage->env);
    // result = function(str, env);
    close_fd(fd_in, fd_out);
    return pipeline->next;
}