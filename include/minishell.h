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
    #include <string.h>
    #include <stdbool.h>
    #include <glob.h>
    #include <stdio.h>
    #define IS_ALPHA(c) (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'))
    #define IS_NUM(c) ('0' <= c && c <= '9')
    #define KEY_UP 1
    #define KEY_DOWN 2
    #define KEY_RIGHT 3
    #define KEY_LEFT 4
    #define KEY_TAB 5
    #define KEY_BACKSPACE 6
    #define KEY_SUPPR 7

typedef struct history_s {
    int id;
    char *time;
    char *command;
    struct history_s *prev;
    struct history_s *next;
} history_t;


typedef struct alias_s {
    char *name;
    char *com;
    struct alias_s *next;
} alias_t;

typedef struct var_s {
    char *var;
    char *value;
    struct var_s *next;
} var_t;

typedef struct token_s {
    char sep;
    char *arg;
    int index;
    struct token_s *prev;
    struct token_s *next;
} token_t;

typedef struct pipeline_s {
    token_t **token_list;
    char *sep;
    int return_value;
    int pid;
    int input;
    int output;
    int error_output;
    struct pipeline_s *next;
} pipeline_t;

typedef struct garbage_s {
    char ***env;
    char **line;
    char **command;
    history_t **history;
    int save_in;
    int save_out;
    int fd[2][2];
    char *raw_command;
    int return_value;
    token_t **token_list;
    pipeline_t **pipeline;
    alias_t *alias;
    var_t *local;
} garbage_t;

typedef struct redirection_tab_s {
    char *sep;
    pipeline_t *(*redirection)(garbage_t *, pipeline_t *);
} redirection_tab_t;

typedef struct builtins_s {
    char *com;
    int (*built)(char *str, char ***env, garbage_t *garbage);
} builtins_t;

typedef struct lexing_tab_s {
    char sep;
    int (*lexing)(garbage_t *, token_t **);
} lexing_tab_t;

extern redirection_tab_t r_tab[];

extern lexing_tab_t l_tab[];

extern builtins_t built[];

token_t **init_token_list(char *str);

void lexing_features(garbage_t *garbage, token_t **token_list);

int parsing_function(garbage_t *garbage, token_t **token_list);

int globbings_function(garbage_t *garbage, token_t **token_list);

int new_process(pipeline_t *pipeline, char **command, char **env);

pipeline_t *execute_semicolon(garbage_t *garbage, pipeline_t *pipeline);

pipeline_t *execute_redirection(garbage_t *garbage, pipeline_t *pipeline);

pipeline_t **init_pipeline(char *str);

void process_execution(garbage_t *garbage, pipeline_t **pipeline);

void free_token_list(token_t **token_list);

void free_pipeline(pipeline_t **pipeline);

pipeline_t *execute_pipe(garbage_t *garbage, pipeline_t *commands);

char *token_to_str(token_t *start);
int get_token_list_size(token_t *token);
char **token_to_str_array(token_t *start, int end);
void insert_spaces(char **input);
void freeing(char *str, char **board);
void format_str(char *str);
int function(char *str, char ***env);
int change_dir(char *str, char ***env, garbage_t *garbage);
char **copy_env(char **env);
int show_env(char *str, char ***env, garbage_t *garbage);
int set_environnement(char *str, char ***env, garbage_t *garbage);
int delete_env(char *str, char ***env, garbage_t *garbage);
int pipe_handling(char *str, char ***env, garbage_t *garbage);
void pipe_redirect(int i, int num_pipe, int pipeline[][2]);
void fork_pipes(char **pipes, int pipeline[][2], int num_pipe,
    garbage_t *garbage);
int redirection_errors(char *command, char **pipes, int i);
int command_errors(char *str, char **pipes, int save_in, int save_out);
void free_alias(garbage_t *garbage);
garbage_t init_local(garbage_t *garbage);
token_t *insert_node(token_t *token, char *com, garbage_t *garbage);
void clean_space(char *str);
void print_token_list(token_t **token_list);
void print_pipeline(pipeline_t **pipeline);
int contain(char *str, char character);
char *array_to_str(char **array);
int check_built(char **command, garbage_t *garbage);
int check_built_on_fork(char **command, char ***env);
int set_alias(char *str, char ***env, garbage_t *garbage);
void free_array(char **arr);
int unalias(char *str, char ***env, garbage_t *garbage);
int set_local(char *str, char ***env, garbage_t *garbage);
int unset_var(char *str, char ***env, garbage_t *garbage);
void free_var(garbage_t *garbage);
token_t *check_varenv(token_t *token, garbage_t *garbage);
token_t *manage_variable(token_t *token, garbage_t *garbage);
token_t *check_local(token_t *token, garbage_t *garbage);
void delete_var(var_t *current, var_t *prev, garbage_t *garbage);
int len_alias(garbage_t *garbage);
void reset_index(garbage_t *garbage);
void delete_alias(alias_t *current, alias_t *prev, garbage_t *garbage);
int var_len(garbage_t *garbage);
token_t *check_alias(token_t *token, garbage_t *garbage);
void ttycheck(void);

void add_history(char *command, history_t **history);
int history_command(char *str, char ***env, garbage_t *garbage);
void clear_history(history_t **history);
void show_reverse_history(history_t **history, int *status_flags);
void show_no_param_history(history_t **history, int *status_flags);
void show_history(history_t **history);
void show_history_num(int num, history_t **history);
int history_up(history_t **tmp, history_t **history, int *cursor);
int history_down(history_t **tmp, int *cursor);

char **my_str_to_minishell_array(char const *str, char *separateur);
int my_c_redi_pipe(char c);
int my_c_pipe(char c);
void add_pipe(char **tab, int **index, char const *str, int *h);
int my_c_redi_r(char c);
int my_c_redi_g(char c);
void add_redi_r(char **tab, int **index, char const *str, int *h);
void add_redi_g(char **tab, int **index, char const *str, int *h);

void display_command(char *line, history_t *tmp, int cursor_mv);
int choose_command(char **line, history_t **tmp, int exit);
void update_command(int ch, char **line, history_t *tmp, int cursor);
void delete_char(char *line, int len, int index);
void insert_char(char *line, int ch, int len, int index);
int my_getline(char **line, size_t *n, history_t **hist);
void set_non_canonical_mode(void);
int is_end(char **line, int len, history_t *tmp, int *cursor_mv);
int is_del(char **line, history_t *tmp, int *cursor, int sp_key);
int arrow_right(int *cursor);
int arrow_left(history_t *tmp, char *line, int *cursor);


#endif
