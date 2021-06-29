/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 13:21:09 by heom              #+#    #+#             */
/*   Updated: 2021/06/29 17:37:17 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef struct	s_charbox
{
	char				*data;
	int					type;
	struct s_charbox	*next;
}				t_charbox;

/*
** one command divided by pipelines
*/
typedef struct	s_cmd
{
	char			*rawcmd;
	char			path[1024];
	t_charbox		*io;
	t_charbox		*argv;
	int				input_mode;
	int				output_mode;
	char			*file_input;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}				t_cmd;


/*
** whole info
*/

typedef struct	s_all
{
	struct s_cmd	*cmd_info;
	char			**dup_envp;
}				t_all;



#endif
