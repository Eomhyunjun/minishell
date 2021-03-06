#ifndef EGGINSHELL_H
# define EGGINSHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include "readline/readline.h"
# include "readline/history.h"
# include <errno.h>
# include "types.h"

# define Q_NONE 0
# define Q_SINGLE 1
# define Q_DOUBLE 2

# define RD_I 0
# define RD_II 1
# define RD_O 2
# define RD_OO 3

# define EGG_ENV 1
# define EGG_EXPORT 2
# define EGG_UNSET 3
# define EGG_ECHO 4
# define EGG_CD 5
# define EGG_EXIT 6
# define EGG_PWD 7

# define ENV_EDIT 'e'
# define ENV_NEW 'n'
# define ENV_NEW_NULL 'b'
# define ENV_UNSET 'u'

# define OTHER_CD 'c'

# define ENVTYPE_STR 0
# define ENVTYPE_NULL 1

# define NO_EXCLUDE -2147483648

t_all
*all(void);

void
init(char **envp);

void
add_cmd(char *rawcmd);

void
safe_exit(int code, char *msg);

void
token_error(char token);

void
free_charbox(t_charbox *charbox);

void
free_char_double_ptr(char **pp);

void
safe_free_cmd(void);

char
*egg_strdup(const char *s1);

char
*egg_strndup(const char *s1, int a, int b);

void
add_charbox(t_charbox **container, char *allocated, int type);

char
*to_chars(t_charbox *charbox, char *div);

int
charbox_len(t_charbox *charbox);

char
**to_double_ptr(t_charbox *charbox, int type_exclude);

int
make_io(void);

int
process_open(t_cmd *current, t_charbox *cur_io, t_charbox *cur_theredoc);

int
try_open(int *fd, char *path, int mode, int permission);

char
**get_path(void);

void
ii_write(void);

void
close_unused(void);

void
wait_subprocess(void);

void
print_export_error(char *data);

void
change_builtin_stdio(t_cmd *current);

void
restore_builtin_stdio(void);

/*
** ----------------- parsing -----------------------
*/

int
can_be_env_name(char c);

int
can_be_first_env_name(char c);

char
*create_dollar(void);

char
*create_blank(void);

int
make_dollar(char *data, int start, char **replaced);

int
get_none_space_pos(char *rawcmd, int i);

int
get_none_name_pos(char *rawcmd, int i);

void
interpret_charbox(t_charbox *charbox);

char
*interpret_quote_env(char *data);

int
is_quote(char c, int *quote);

int
is_empty(char *content);

int
make_cmd_item(t_cmd *current);

int
make_rawcmd(char *buf);

int
make_cmd(void);

int
parse(char *buf);

int
argv_try_push(t_cmd *current, int i);

int
io_try_push(t_cmd *current, int *i);

/*
** ---------------- signal --------------------------
*/

void
do_nothing(int signo);

void
sigint_handler(int signo);

int
custom_rl_getc_fuction(FILE *stream);

/*
** ---------------- builtin_cmd -------------------
*/

int
egg_env(t_cmd *cur_cmd);

int
egg_export(t_cmd *cmd);

int
egg_unset(t_cmd *cmd);

int
egg_echo(t_cmd *cmd);

int
egg_cd(t_cmd *cmd);

int
egg_pwd(void);

int
egg_exit(t_cmd *cmd);

int
validate_export(char *data, char **name, char **value);

void
process_env_pipe(void);

void
process_exit_pipe(void);

void
process_other_pipe(void);

t_charbox
*find_envp(char *name);

int
send_env_code(char type, char *name, char *value);

char
*create_from_env(char *name);

/*
** ---------------   envp -------------------
*/

int
add_new_envp(char *name, char *value);

int
edit_envp(char *name, char *value);

void
unset_envp(char *name);

int
update_envp(char *name, char *value);

/*
** ----------------   execve   ----------------------
*/

void
make_pipe(void);

void
fork_loop(void);

int
try_execve(t_cmd *current);

int
check_builtin_cmd(t_cmd *current);

int
exec_builtin_cmd(t_cmd *current);

int
check_dir(t_cmd *current);

void
exec_dir_cmd(t_cmd *current, t_exec *t);

void
do_child(t_cmd *current);

void
exec_path_cmd(t_cmd *current, t_exec *t);

/*
** ----------------   utils   ----------------------
*/
int
ft_atoi(const char *str);

char
*ft_itoa(int n);

void
ft_bzero(void *s, size_t n);

int
ft_strncmp(const char *s1, const char *s2, size_t n);

void
ft_putstr_plus_newline(int fd, const char *s);

int
ft_strcmp(const char *s1, const char *s2);

int
ft_strlen(const char *str);

char
**ft_split(char const *s, char c);

size_t
ft_strlcpy(char *dst, const char *src, size_t size);

int
ft_malloc(void *pp, size_t size);

char
*ft_strjoin3(char const *s1, char const *mid, char const *s2);

char
*ft_strjoin4(char const *s1, char const *s2, char const *s3, char const *s4);

#endif
