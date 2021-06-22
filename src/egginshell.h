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

t_all
*all(void);

void
add_cmds(void);

void
add_cmd(char *rawcmd);

void
safe_exit(int code, char *msg);

/*
** utils
*/

void
ft_bzero(void *s, size_t n);

char
*ft_strndup(const char *s1, int a, int b);



#endif
