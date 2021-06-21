/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 15:57:11 by heom              #+#    #+#             */
/*   Updated: 2021/06/21 16:40:39 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

void	add_cmds(void)
{
	t_cmds *new_cmds;
	t_cmds *last_cmds;

	if (all()->cmds == NULL)
	{
		all()->cmds = malloc(sizeof(t_cmds));
		ft_bzero(all()->cmds, sizeof(t_cmds));
		return ;
	}
	new_cmds = malloc(sizeof(t_cmds));
	ft_bzero(new_cmds, sizeof(t_cmds));
	last_cmds = all()->cmds;
	while (last_cmds->next != NULL)
		last_cmds = last_cmds->next;
	last_cmds->next = new_cmds;
	new_cmds->prev = last_cmds;
}

void	add_cmd(t_cmd **cmd_info)
{
	t_cmd *new_cmd;
	t_cmd *last_cmd;

	if (*cmd_info == NULL)
	{
		*cmd_info = malloc(sizeof(t_cmd));
		ft_bzero(*cmd_info, sizeof(t_cmd));
		printf("hi\n");
		return ;
	}
	new_cmd = malloc(sizeof(t_cmd));
	ft_bzero(new_cmd, sizeof(t_cmd));
	last_cmd = *cmd_info;
	while (last_cmd->next != NULL)
		last_cmd = last_cmd->next;
	last_cmd->next = new_cmd;
	new_cmd->prev = last_cmd;
}
