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

static int contain(char *str, char character)
{
    for (int i = 0; str[i]; i++) {
        if (str[i] == character)
            return 1;
    }
    return 0;
}

static int test_relative(char **command, char **path)
{
    struct stat file;

    if (access(command[0], F_OK) == -1) {
        write(2, command[0], my_strlen(command[0]));
        write(2, ": Command not found.\n", 21);
        freeing(0, command);
        return 1;
    }
    if (access(command[0], X_OK) == -1 || stat(command[0], &file) == -1 ||
    !S_ISREG(file.st_mode)) {
        write(2, command[0], my_strlen(command[0]));
        write(2, ": Permission denied.\n", 21);
        freeing(0, command);
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
        freeing(*path, 0);
        *path = malloc(my_strlen(path_var[i]) + my_strlen(command[0]) + 2);
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
    if (test_path(path_var, command, path)) {
        freeing(*path, path_var);
        freeing(0, command);
        return 1;
    }
    freeing(0, path_var);
    return 0;
}

static int segfault_exit(int status)
{
    write(2, "Segmentation fault", 18);
    if (WCOREDUMP(status))
        write(2, " (core dumped)", 14);
    write(2, "\n", 1);
    return 139;
}

static int return_status(int status)
{
    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    if (WIFSIGNALED(status))
        if (WTERMSIG(status) == SIGSEGV)
            return segfault_exit(status);
    return 1;
}

int new_process(char *str, char **env)
{
    int pid;
    int status;
    char *path = 0;
    char **command = my_str_to_array(str, " ");

    if (get_command(command, env, &path))
        return 1;
    pid = fork();
    if (pid == -1)
        exit(84);
    if (pid == 0) {
        execve(path, command, env);
        if (errno == ENOEXEC)
            error_write(path, ": Exec format error. Wrong Architecture.\n");
        exit(1);
    } else
        waitpid(pid, &status, 0);
    freeing(path, command);
    return return_status(status);
}
