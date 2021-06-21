#ifndef EGGINSHELL_H
# define EGGINSHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "types.h"

t_all
*all(void);

void
add_cmds(void);

void
add_cmd(t_cmd **cmd_info);

/*
** utils
*/

void
ft_bzero(void *s, size_t n);



#endif
