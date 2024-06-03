/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-nicolas.dumetz
** File description:
** display_tab.c
*/

#include "../../include/minishell.h"

static void comp_com(DIR *dir, char *word)
{
    struct dirent *dp;

    dp = readdir(dir);
    while (dp != NULL) {
        if (my_strncmp(dp->d_name, word, strlen(word)) == 0)
            printf("%s  ", dp->d_name);
        dp = readdir(dir);
    }
}

static void display_comp_com(getline_t *getmy)
{
    char *path = getenv("PATH");
    char **path_tokens = my_str_to_word_array_char(path, ":");
    DIR *dir;

    for (int i = 0; path_tokens[i] != NULL; i++) {
        dir = opendir(path_tokens[i]);
        if (dir != NULL) {
            comp_com(dir, getmy->word);
            closedir(dir);
        }
    }
}

static char *is_dir(char *name, char *path)
{
    struct stat s;
    char *copy = malloc(sizeof(char) * (strlen(name) + strlen(path) + 1));

    if (copy == NULL)
        return "  ";
    copy = strcpy(copy, path);
    copy = strcat(copy, name);
    if (stat(copy, &s) != 0) {
        free(copy);
        return "  ";
    }
    if (S_ISDIR(s.st_mode)) {
        free(copy);
        return "/  ";
    } else {
        free(copy);
        return "  ";
    }
}

static void display_file(struct dirent *dp, char *word, char *path)
{
    if (dp->d_name[0] != '.' || word[0] == '.') {
        printf("%s", dp->d_name);
        printf("%s", is_dir(dp->d_name, path));
    }
}

static void comp_file(DIR *dir, char *word, char *path)
{
    struct dirent *dp;

    dp = readdir(dir);
    while (dp != NULL) {
        if (strncmp(dp->d_name, word, strlen(word)) == 0) {
            display_file(dp, word, path);
        }
        dp = readdir(dir);
    }
}

static void display_comp_file(getline_t *getmy)
{
    char *path = get_path_autocompletion(getmy->word);
    DIR *dir;
    int i = strlen(getmy->word) - 1;

    if (path == NULL)
        return;
    dir = opendir(path);
    if (dir == NULL)
        return;
    for (; i >= 0 && getmy->word[i] != '/'; i--);
    comp_file(dir, &(getmy->word[i + 1]), path);
    closedir(dir);
    free(path);
}

void display_tab(getline_t *getmy)
{
    printf("\n");
    if (getmy->tab == 1)
        display_comp_com(getmy);
    if (getmy->tab == 2)
        display_comp_file(getmy);
    printf("\n");
    getmy->tab = -1;
}
