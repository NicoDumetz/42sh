/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-matisse.dufour
** File description:
** env.c
*/

#include <stdlib.h>
#include <unistd.h>
#include "my.h"
#include "minishell.h"

#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

static int is_exec(char *file)
{
    struct stat st;

    if (stat(file, &st) == 0)
        if (st.st_mode & S_IXUSR)
            return (1);
    return (0);
}

static int check_dir(char *command, struct dirent *dir, char *path)
{
    char file[my_strlen(command) + my_strlen(path) + 1];

    if (my_strcmp(command, dir->d_name) != 0)
        return (0);
    file[0] = '\0';
    my_strcat(file, path);
    if (path[my_strlen(path) - 1] != '/')
    my_strcat(file, "/");
    my_strcat(file, command);
    if (is_exec(file) == 1) {
        printf("%s\n", file);
        return (1);
    } else
        return (0);
}

static int is_here(char *command, char *path)
{
    DIR *d;
    struct dirent *dir;

    d = opendir(path);
    if (!d)
        return 0;
    dir = readdir(d);
    while ((dir != NULL)) {
        if (check_dir(command, dir, path) == 1) {
            closedir(d);
            return 1;
        }
        dir = readdir(d);
    }
    closedir(d);
    return 0;
}

int do_where(char *command, char **all_path)
{
    int check = 0;

    for (int i = 0; all_path[i]; i++)
        check += is_here(command, all_path[i]);
    if (check > 0)
        return 0;
    for (int i = 0; built[i].com; i++)
        if (my_strcmp(built[i].com, command) == 0) {
            printf("%s is a shell built-in command.\n", command);
            return (0);
        }
    return 1;
}

int do_which(char *command, char **all_path)
{
    for (int i = 0; all_path[i]; i++)
        if (is_here(command, all_path[i]) == 1)
            return 0;
    for (int i = 0; built[i].com; i++)
        if (my_strcmp(built[i].com, command) == 0) {
            printf("%s: shell built-in command.\n", command);
            return (0);
        }
    fprintf(stderr, "%s :Command not found.\n", command);
    return 1;
}

int which_functions(char *str, char ***, garbage_t *)
{
    char **command = my_str_to_array(str, " ");
    char *path_value = getenv("PATH");
    char **all_path = my_str_to_array(path_value, ":");
    int check = 0;

    if (all_path == NULL)
        return 1;
    if (command[1] == NULL) {
        fprintf(stderr, "%s: Too few arguments.\n", command[0]);
        freeing(0, all_path);
        free_array(command);
        return 1;
    }
    for (int i = 1; command[i]; i++)
        check -= do_which(command[i], all_path);
    if (check < 0)
        check = 1;
    freeing(0, all_path);
    free_array(command);
    return check;
}

int where_functions(char *str, char ***, garbage_t *)
{
    char **command = my_str_to_array(str, " ");
    char *path_value = getenv("PATH");
    char **all_path = my_str_to_array(path_value, ":");
    int check = 0;

    if (all_path == NULL)
        return 1;
    if (tab_len(command) < 2) {
        fprintf(stderr, "%s: Too few arguments.\n", command[0]);
        freeing(0, all_path);
        free_array(command);
        return 1;
    }
    for (int i = 1; command[i]; i++)
        check -= do_where(command[i], all_path);
    if (check < 0)
        check = 1;
    freeing(0, all_path);
    free_array(command);
    return check;
}
