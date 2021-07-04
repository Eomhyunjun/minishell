#ifndef EGGINSHELL_H
# define EGGINSHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "types.h"

# define Q_NONE 0
# define Q_SINGLE 1
# define Q_DOUBLE 2

# define RD_I 0
# define RD_II 1
# define RD_O 2
# define RD_OO 3

t_all
*all(void);

void
parse(char *buf);

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
make_rawcmd(char *buf);

void
make_cmd(void);

void
make_cmd_item(t_cmd *current);

int
get_none_space_pos(char *rawcmd, int i);

int
get_none_name_pos(char *rawcmd, int i);

char
*egg_strdup(const char *s1);

char
*egg_strndup(const char *s1, int a, int b);


int
is_quote(char c, int *quote);

int
argv_try_push(t_cmd *current, int i);

int
io_try_push(t_cmd *current, int i);

void
add_charbox(t_charbox **container, char *allocated, int type);

char
*to_chars(t_charbox *charbox, char *div);

char
**to_double_ptr(t_charbox *charbox);

void
interpret_charbox(t_charbox *charbox);

char
*interpret_quote_env(char *data);


int
make_dollar(char *data, int start, char **replaced);

void
try_open_for_read(int *fd, char *path);

char
**get_path(void);

/*
** ----------------   pipe   ----------------------
*/

void
make_pipe(void);

void
fork_loop(void);

/*
** ----------------   utils   ----------------------
*/

void
ft_bzero(void *s, size_t n);

int
ft_strncmp(const char *s1, const char *s2, size_t n);

void
ft_putstr(int fd, const char *s);

int
ft_strcmp(const char *s1, const char *s2);

int
ft_strlen(const char *str);

char
**ft_split(char const *s, char c);

unsigned int
ft_strlcpy(char *dest, char *src, unsigned int size);

int
ft_malloc(void *pp, size_t size);

char
*ft_strjoin(char const *s1, char const *mid, char const *s2);


#endif
