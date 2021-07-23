/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 13:21:09 by heom              #+#    #+#             */
/*   Updated: 2021/07/23 16:04:56 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <limits.h>
# include <termios.h>

typedef struct s_charbox
{
	char				*data;
	int					type;
	struct s_charbox	*next;
	struct s_charbox	*prev;
}				t_charbox;

typedef struct s_oil
{
	t_charbox	*box;
	char		*data;
	int			quote;
	int			start;
	int			i;
}				t_oil;

/*
** one command divided by pipelines
*/
typedef struct s_cmd
{
	char			*rawcmd;
	t_charbox		*io;
	t_charbox		*argv;
	t_charbox		*theredoc;
	t_charbox		*last_input;
	t_charbox		*last_output;
	int				input_fd;
	int				output_fd;
	int				pipe_fd[2];
	int				ii_fd[2];
	int				pid;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}				t_cmd;

/*
** whole info
*/

typedef struct s_all
{
	struct s_cmd		*cmd_info;
	struct s_charbox	*egg_envp;
	char				**path;
	struct termios		oldtio;
	int					last_cmd_result;
	int					builtin_stdin;
	int					builtin_stdout;
}				t_all;

typedef struct s_exec
{
	char	**argv_matrix;
	char	**envp_matrix;
	char	*exec_path;
	char	*cwd;
	char	*msg;
	int		i;
	int		ret;
}			t_exec;

#endif
