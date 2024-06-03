/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-matisse.dufour
** File description:
** new_process.c
*/
#include "minishell.h"
#include "my.h"
#include <asm-generic/errno.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static int test_relative(char **command, char **path)
{
    struct stat file;

    if (access(command[0], F_OK) == -1) {
        write(2, command[0], my_strlen(command[0]));
        write(2, ": Command not found.\n", 21);
        return 1;
    }
    if (access(command[0], X_OK) == -1 || stat(command[0], &file) == -1 ||
    !S_ISREG(file.st_mode)) {
        write(2, command[0], my_strlen(command[0]));
        write(2, ": Permission denied.\n", 21);
        return 1;
    }
    *path = my_strdup(command[0]);
    return 0;
}

static char **get_path(char **env)
{
    int i = 0;

    for (; env[i] && my_strncmp(env[i], "PATH=", 5) != 0; i++);
    if (!env[i])
        return my_str_to_array("", ":");
    return my_str_to_array(env[i] + 5, ":");
}

static void error_write(char *command, char *message)
{
    write(2, command, my_strlen(command));
    write(2, message, my_strlen(message));
}

static int test_path(char **path_var, char **command, char **path)
{
    struct stat file_stat;

    for (int i = 0; path_var[i]; i++) {
        *path = gmalloc(my_strlen(path_var[i]) + my_strlen(command[0]) + 2);
        my_strcpy(*path, path_var[i]);
        my_strcat(*path, "/");
        my_strcat(*path, command[0]);
        if (access(*path, F_OK) == -1)
            continue;
        if (access(*path, X_OK) == -1 || stat(*path, &file_stat) == -1 ||
        !S_ISREG(file_stat.st_mode)) {
            error_write(command[0], ": Permission denied.\n");
            return 1;
        }
        return 0;
    }
    error_write(command[0], ": Command not found.\n");
    return 1;
}

static int get_command(char **command, char **env, char **path)
{
    char **path_var;

    if (contain(command[0], '/'))
        return test_relative(command, path);
    path_var = get_path(env);
    if (strcmp(command[0], "setenv") != 0 &&
        strcmp(command[0], "repeat") != 0 &&
        test_path(path_var, command, path)) {
        return 1;
    }
    return 0;
}

static void on_fork(
    pipeline_t *node, char **command, garbage_t *garbage, char *path)
{
    if (node->input != STDIN_FILENO)
        dup2(node->input, STDIN_FILENO);
    if (node->output != STDOUT_FILENO)
        dup2(node->output, STDOUT_FILENO);
    if (command[0] == NULL || get_command(command, *garbage->env, &path))
        exit(EXIT_FAILURE);
    if (check_built_on_fork(command, garbage->env, node, garbage) != 0)
        return;
    else
        execve(path, command, *garbage->env);
    if (errno == ENOEXEC)
        error_write(path, ": Exec format error. Wrong Architecture.\n");
    exit(EXIT_FAILURE);
}

static void reset_in_and_out(pipeline_t *node)
{
    if (node->input != STDIN_FILENO)
        close(node->input);
    if (node->output != STDOUT_FILENO)
        close(node->output);
}

int new_process(
    pipeline_t *node, char **command, char **, garbage_t *garbage)
{
    int pid;
    char *path = 0;

    pid = fork();
    if (pid == -1)
        exit(84);
    if (pid == 0) {
        on_fork(node, command, garbage, path);
    } else {
        node->pid = pid;
        reset_in_and_out(node);
    }
    return 0;
}
