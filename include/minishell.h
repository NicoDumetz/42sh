/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-matisse.dufour
** File description:
** minishell.h
*/

#ifndef MINISHELL_HEADER
    #define MINISHELL_HEADER
    #define IS_ALPHA(c) (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'))
    #define IS_NUM(c) ('0' <= c && c <= '9')
typedef struct garbage_s {
    char ***env;
    char **line;
    char **command;
    int save_in;
    int save_out;
} garbage_t;
void freeing(char *str, char **board);
void format_str(char *str);
int function(char *str, char ***env);
int change_dir(char *str, char ***env);
char **copy_env(char **env);
int show_env(char **env);
int set_environnement(char *str, char ***env);
int delete_env(char *str, char ***env);
int new_process(char *str, char **env);
int pipe_handling(char *str, char ***env, garbage_t *garbage);
void pipe_redirect(int i, int num_pipe, int pipeline[][2]);
void fork_pipes(char **pipes, int pipeline[][2], int num_pipe,
    garbage_t *garbage);
int redirection(char *str, char ***env, int save_out);
int redirection_errors(char *command, char **pipes, int i);
int command_errors(char *str, char **pipes, int save_in, int save_out);
#endif
