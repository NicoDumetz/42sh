/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-nicolas.dumetz
** File description:
** prompt.c
*/

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <pwd.h>

int get_prompt_size(void)
{
    char hostname[1024];
    char username[1024];
    char cwd[1024];
    struct passwd *pw = getpwuid(getuid());

    if (gethostname(hostname, sizeof(hostname)) == 0 && pw != NULL) {
        strcpy(username, pw->pw_name);
        if (getcwd(cwd, sizeof(cwd)) != NULL)
            return my_strlen(username) + my_strlen(hostname) + my_strlen(cwd)
            + 5;
    }
    return 0;
}

static void display_prompt(void)
{
    char hostname[1024];
    char username[1024];
    char cwd[1024];
    struct passwd *pw = getpwuid(getuid());

    if (gethostname(hostname, sizeof(hostname)) == 0 && pw != NULL) {
        strcpy(username, pw->pw_name);
        if (getcwd(cwd, sizeof(cwd)) != NULL)
            my_printf("\033[92m%s\033[0m@\033[92m%s\033"
                "[0m:\033[34m%s$>\033[0m ", username, hostname, cwd);
    }
}

void ttycheck(void)
{
    if (isatty(STDIN_FILENO))
        display_prompt();
}
