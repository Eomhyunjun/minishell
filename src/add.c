/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 15:57:11 by heom              #+#    #+#             */
/*   Updated: 2021/06/29 20:38:53 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

void	add_cmd(char *rawcmd)
{
	t_cmd *new_cmd;
	t_cmd *last_cmd;

	if ((new_cmd = malloc(sizeof(t_cmd))) == 0)
		safe_exit(1, "new_cmd malloc failed!");
	ft_bzero(new_cmd, sizeof(t_cmd));
	new_cmd->rawcmd = rawcmd;
	if (all()->cmd_info == NULL)
	{
		all()->cmd_info = new_cmd;
		return ;
	}
	last_cmd = all()->cmd_info;
	while (last_cmd->next != NULL)
		last_cmd = last_cmd->next;
	last_cmd->next = new_cmd;
	new_cmd->prev = last_cmd;
}
