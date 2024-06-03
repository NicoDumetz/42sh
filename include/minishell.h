/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-minishell1-matisse.dufour
** File description:
** minishell.h
*/

#ifndef MINISHELL_HEADER
    #define MINISHELL_HEADER
    #include "my.h"
    #include <stdlib.h>
    #include <stdio.h>
    #define IS_ALPHA(c) (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'))
    #define IS_NUM(c) ('0' <= c && c <= '9')
    #define KEY_UP 1
    #define KEY_DOWN 2
    #define KEY_RIGHT 3
    #define KEY_LEFT 4
    #define KEY_TAB 5
    #define KEY_BACKSPACE 6
typedef struct garbage_s {
    char ***env;
    char **line;
    char **command;
    int save_in;
    int save_out;
} garbage_t;
typedef struct history_s {
    int id;
    char *time;
    char *command;
    struct history_s *prev;
    struct history_s *next;
} history_t;
void insert_spaces(char **input);
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
void ttycheck(void);

void add_history(char *command, history_t **history);
int history_command(char *str, history_t **history);
void clear_history(history_t **history);
void show_reverse_history(history_t **history, int *status_flags);
void show_no_param_history(history_t **history, int *status_flags);
void show_history(history_t **history);
void show_history_num(int num, history_t **history);
void history_up(history_t **tmp, history_t **history);
void history_down(history_t **tmp);

char **my_str_to_minishell_array(char const *str, char *separateur);
int my_c_redi_pipe(char c);
int my_c_pipe(char c);
void add_pipe(char **tab, int **index, char const *str, int *h);
int my_c_redi_r(char c);
int my_c_redi_g(char c);
void add_redi_r(char **tab, int **index, char const *str, int *h);
void add_redi_g(char **tab, int **index, char const *str, int *h);

int my_getline(char **line, size_t *n, history_t **hist);
void set_non_canonical_mode();
int is_end(char **line, int len);
void is_del(char **line, int len);


#endif
