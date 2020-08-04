#ifndef USH_H
#define USH_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/stat.h>
#include <pwd.h>
#include <ctype.h>
#include <termios.h>
#include <signal.h>
#include <limits.h>
#include "./libmx/inc/libmx.h"

#define MX_NUM_COM  9
#define MX_NUM_SPEC  8
#define MX_NUM_SPEC2  5
#define MX_TD " \t\r\n\a"
#define MX_IFMT 0170000
#define MX_IFLNK 0120000
#define MX_TOK 200

typedef struct s_data {
    int *n_val;
    char ***st_val_c;
    int *spec;
    int *spec2;
    char **wr_spec;
    int *fd;
    int fd_type;
    char *fd_name_z;
    char *fd_name_in;
    int fd_zap;
    int fd_in;
    int fd_1_def;
    int child;
    char **names;
    int n_reserv;
    char **reserved;
    int flag;
    int n_h;
    int n_h_t;
    char **hist;
    int e;
    int b;
    int cur;
    int c_b;
    int exi_t;
    int *sigi;
    char **signals;
    struct termios old_term;
    int n;
    int *delim;
    int *path;
    int satty;
    int proc;
}   t_data;

typedef struct s_split {
    int n;
    int f_q;
    int f_dq;
    char *line;
    char **tok;
    int n_t;
    char *temp;

}   t_split;

typedef struct s_lvg {
    int a;
    char *value;
    char *znach;
    int fdp;
    int sign;
}   t_lvg;

extern char **environ;

t_data *mx_initial(void);

int mx_make_command(t_data *dat);

int mx_atoi(char *str);

char *mx_command_create(char *str, int *y, int type, t_data *dat);

void *mx_free(void *arr);

void mx_free_struct(t_data *dat);

char *mx_readline(char *str, t_data *dat);

int *mx_init_int(int value, int num);

char **mx_init_wr_spec(void);

char **mx_split_line(int *num, char **line, t_data *dat);

int mx_local_value_in(char **tok, int num, t_data *dat);

char *mx_file_to_str_edited(const int fd);

int mx_exit(char **str, int num, t_data *dat);

char **mx_free_array(char **arr, int row);

int mx_create_process(int a, char **token, int num, t_data *dat);

void mx_signals(int in);

int mx_spec_commands(char *red, int b, t_data *dat);

void mx_print_folder(t_data *dat);

int mx_change_term(int flag, t_data *dat);

char *mx_run_doch(char *str, int *flag, int *n_end_sign, t_data *dat);

int mx_swit( int a, char **str, int num, t_data *dat);

int mx_builtin_command(char **token, t_data *dat);

void mx_input_clear(t_data *dat);

int mx_echo(char **str, int num, t_data *dat);

char *mx_if_outher(char *str, int *flag, int *n_end_sign, t_data *dat);

char *mx_local_value_get(char *str, int *flag, t_data *dat);

char *mx_local_value_get2(char *str, int *flag, t_data *dat);

int mx_fg(char **tokens, int num, t_data *dat);

int mx_env(char **str, int num, t_data *dat);

int mx_cd(char **str, int num, t_data *dat);

int mx_pwd(char **tokens, int num, t_data *dat);

int mx_unset(char **str, int num, t_data *dat);

int mx_which(char **str, int num, t_data *dat);

int mx_export(char **str, int num, t_data *dat);

int mx_env_i(char **str, int num, int a, t_data *dat);

void mx_env_run(char **str, int num, int a, char *path);

char *mx_cd_get_path(char **str, int num, int *f, t_data *dat);

int mx_clearenv(void);

void mx_env_print_error(char **in);

char *mx_cd_tilda(char *str, int *i, t_data *dat) ;

void ***mx_free_array3(void ***arr, int row, int col);

int mx_if_escape(char *str, int a, t_split *s);

int *mx_array_dup(int *arr, int num, int val);

void mx_local_value_in2(t_data *dat, char **str, int c, char *tok);

int mx_read_get_line(t_data *dat);

void mx_read_pr_home(t_data *dat);

int mx_read_check_quotes(char **res, int *out, t_data *dat);

int mx_split_files(char *str, int *a, int *flag, t_data *dat);

int mx_split_symbols(char *str, int *a, t_split *s, t_data *dat);

void mx_restart_proc(int pid, int *flag, int n, t_data *dat);

void mx_sig_exit(int sig);

t_split *mx_split_main_dop(char *str, int a, t_split *s);

t_lvg *mx_init_lvg(void);

void mx_sig_pause(int sig);

void mx_quote_4(char *str, int b, int *out, t_data *dat);

char *mx_check_path(char *path, int i);

#endif
