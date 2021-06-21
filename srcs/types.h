/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 13:21:09 by heom              #+#    #+#             */
/*   Updated: 2021/06/21 16:28:49 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

/*
** one command divided by pipelines
*/
typedef struct	s_cmd
{
	char			cmd[256];
	char			**argv;
	int				input_mode;
	int				output_mode;
	char			**rds;
	char			**rrds;
	char			*file_input;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}				t_cmd;


/*
** whole line
*/
typedef struct s_cmds
{
	struct s_cmd	*cmd_info;
	struct s_cmds	*next;
	struct s_cmds	*prev;
}				t_cmds;


/*
** whole info
*/

typedef struct	s_all
{
	struct s_cmds	*cmds;
	char			**dup_envp;
}				t_all;



#endif
