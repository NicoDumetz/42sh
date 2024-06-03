/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-nicolas.dumetz
** File description:
** completion_file.c
*/

#include "../../include/minishell.h"
#include <unistd.h>

static void format_path(char *word, int len, char *path)
{
    int i;
    char *copy = strdup(word);

    for (i = len - 1; i >= 0; i--) {
        if (word[i] == '/')
            break;
    }
    copy[i + 1] = '\0';
    path = strcat(path, copy);
    free(copy);
}

static char *written_pass(char *word, int len)
{
    char *path = malloc(sizeof(char) * strlen(word) + 1);
    char *copy = strdup(word);
    int i;

    if (path == NULL)
        return NULL;
    for (i = len - 1; i >= 0; i--) {
        if (word[i] == '/')
            break;
    }
    copy[i + 1] = '\0';
    path = strcpy(path, copy);
    free(copy);
    return path;
}

char *get_path_autocompletion(char *word)
{
    int len = strlen(word);
    char *path;
    int slash = 0;

    if (word[0] == '/')
        return written_pass(word, len);
    path = malloc(sizeof(char) * 1024 + len);
    if (path == NULL)
        return NULL;
    if (getcwd(path, 1024 + len) == NULL)
        return NULL;
    path = strcat(path, "/");
    for (int i = 0; word[i] != '\0'; i++) {
        if (word[i] == '/')
            slash++;
    }
    if (slash != 0)
        format_path(word, len, path);
    return path;
}

static void set_completed(char **completed, char *name, char *path)
{
    struct stat s;
    char *copy = malloc(sizeof(char) * (strlen(name) + strlen(path) + 1));

    *completed = strdup(name);
    if (copy == NULL && *completed == NULL)
        return;
    copy = strcpy(copy, path);
    copy = strcat(copy, name);
    if (stat(copy, &s) != 0)
        return;
    *completed = realloc(*completed, sizeof(char) * (strlen(name) + 2));
    if (S_ISDIR(s.st_mode)) {
        *completed = strcat(*completed, "/");
    } else
        *completed = strcat(*completed, " ");
    free(copy);
}

static int read_file_dir(DIR *dir, char *word, char *path, char
    **completed)
{
    struct dirent *dp;
    int count = 0;

    dp = readdir(dir);
    while (dp != NULL) {
        if (count > 1)
            return count;
        if (strncmp(dp->d_name, word, strlen(word)) == 0) {
            set_completed(completed, dp->d_name, path);
            count += 1;
        }
        dp = readdir(dir);
    }
    return count;
}

static int search_file(char *word, char **completed, int len_word)
{
    char *path = get_path_autocompletion(word);
    int count;
    DIR *dir;
    int i = len_word - 1;

    if (path == NULL)
        return 0;
    dir = opendir(path);
    if (dir == NULL)
        return 0;
    for (; i >= 0 && word[i] != '/'; i--);
    count = read_file_dir(dir, &word[i + 1], path, completed);
    closedir(dir);
    free(path);
    return count;
}

static char *complete_file(char *completed, char *word, int len_word)
{
    char *copy = strdup(completed);
    int i;

    for (i = len_word - 1; i >= 0 && word[i] != '/'; i--);
    word[i + 1] = '\0';
    free(completed);
    completed = NULL;
    completed = malloc(sizeof(char) * (strlen(copy) +
        strlen(word) + 1));
    if (completed == NULL)
        return copy;
    completed = strcpy(completed, word);
    completed = strcat(completed, copy);
    free(copy);
    return completed;
}

static void set_word(char *word, getline_t *getmy)
{
    if (getmy->word != NULL) {
        free(getmy->word);
        getmy->word = NULL;
    }
    getmy->word = strdup(word);
}

void auto_completion_file(char *word, char **line, getline_t *getmy)
{
    char *completed = NULL;
    int len_word;
    int count;

    len_word = strlen(word);
    count = search_file(word, &completed, len_word);
    if (count == 0)
        return;
    if (count == 1) {
        completed = complete_file(completed, word, len_word);
        complete_command(line, completed, strlen(*line), getmy);
    } else {
        set_word(word, getmy);
        getmy->tab = 2;
    }
    if (completed != NULL)
        free(completed);
}

void completion_file(char **tab_word, char **line, int count_word,
    getline_t *getmy)
{
    char *word = "";

    if (count_word != 0 && count_word <= tab_len(tab_word))
        word = tab_word[count_word - 1];
    auto_completion_file(word, line, getmy);
}
