/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-matisse.dufour
** File description:
** cd.c
*/
#include "my.h"
#include "minishell.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int error_check(int i)
{
    if (i > 2) {
        write(2, "cd: Too many arguments.\n", 24);
        return 1;
    }
    return 0;
}

static char *get_home(char **env)
{
    char *home = 0;

    for (int i = 0; env[i]; i++) {
        if (my_strncmp(env[i], "HOME=", 5) == 0) {
            home = my_strdup(env[i] + 5);
            break;
        }
    }
    if (home != 0 && home[0] == '\0') {
        free(home);
        return 0;
    }
    return home;
}

static char *get_path(char *str, char **env)
{
    char *path;
    char *home;

    if (str == 0)
        return get_home(env);
    if (str[0] == '~') {
        home = get_home(env);
        if (home == 0)
            return 0;
        path = malloc(my_strlen(home) + my_strlen(str));
        my_strcpy(path, home);
        my_strcat(path, str + 1);
        free(home);
    } else {
        path = my_strdup(str);
    }
    return path;
}

static void chdir_errors(char *path)
{
    char *error_message = strerror(errno);

    write(2, path, my_strlen(path));
    write(2, ": ", 2);
    write(2, error_message, my_strlen(error_message));
    write(2, ".\n", 2);
    free(path);
}

static char *find_path(char **command, char **env, char *prev_path)
{
    if (command[1] && my_strcmp(command[1], "-") == 0)
        return my_strdup(prev_path);
    else
        return get_path(command[1], env);
}

static int cd_loop(char *path, char **command, char **env)
{
    static char prev_path[1024] = {' ', '\0'};
    char *actual_path = getcwd(0, 0);

    path = find_path(command, env, prev_path);
    if (path == 0) {
        freeing(actual_path, command);
        return 1;
    }
    if (chdir(path) == -1) {
        chdir_errors(path);
        freeing(actual_path, command);
        return 1;
    }
    if (my_strlen(actual_path) < 1024)
        my_strcpy(prev_path, actual_path);
    free(actual_path);
    freeing(path, command);
    return 0;
}

int change_dir(char *str, char ***env, garbage_t *garbage)
{
    char **command;
    char *path;
    int i = 0;
    char *new_pwd;

    command = my_str_to_array(str, " ");
    for (; command[i]; i++);
    if (error_check(i)) {
        freeing(0, command);
        return 1;
    }
    i = cd_loop(path, command, *env);
    new_pwd = getcwd(0, 0);
    path = malloc(my_strlen("setenv PWD ") + my_strlen(new_pwd) + 1);
    my_strcpy(path, "setenv PWD ");
    my_strcat(path, new_pwd);
    set_environnement(path, env, garbage);
    free(path);
    free(new_pwd);
    return i;
}
