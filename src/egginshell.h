#ifndef EGGINSHELL_H
# define EGGINSHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "readline/readline.h"
# include "readline/history.h"
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
init(char **envp);

void
add_cmd(char *rawcmd);

void
safe_exit(int code, char *msg);

void
token_error(char token);

void
safe_charbox_free(t_charbox *current);

void
make_argv_item(t_cmd *current);

void
make_argv(void);

int
get_none_space_pos(char *rawcmd, int i);

int
get_none_name_pos(char *rawcmd, int i);

char
*egg_strndup(const char *s1, int a, int b);

int
is_quote(char c, int *quote);

int
cmd_try_push(t_cmd *current, int i);

int
io_try_push(t_cmd *current, int i);

void
add_charbox(t_charbox **container, char *allocated, int type);

char
*to_chars(t_charbox *charbox);

void
interpret_quote_env(t_cmd *cmd);

char
*interpret_quote_env_item(char *data);
/*
** utils
*/

void
ft_bzero(void *s, size_t n);

int
ft_strncmp(const char *s1, const char *s2, size_t n);




#endif
