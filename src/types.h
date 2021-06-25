/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 13:21:09 by heom              #+#    #+#             */
/*   Updated: 2021/06/25 17:14:22 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef struct	s_charsbox
{
	char				*data;
	int					type;
	struct s_charsbox	*next;
}				t_iobox;

/*
** one command divided by pipelines
*/
typedef struct	s_cmd
{
	char			*rawcmd;
	char			path[1024];
	char			**argv;
	int				input_mode;
	int				output_mode;
	t_iobox			*io;
	char			*file_input;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}				t_cmd;



/*
** whole line
*/
// typedef struct s_cmds
// {
// 	struct s_cmd	*cmd_info;
// 	struct s_cmds	*next;
// 	struct s_cmds	*prev;
// }				t_cmds;


/*
** whole info
*/

typedef struct	s_all
{
	struct s_cmd	*cmd_info;
	char			**dup_envp;
}				t_all;



#endif
