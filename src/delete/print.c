/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 14:25:06 by heom              #+#    #+#             */
/*   Updated: 2021/07/19 20:39:03 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

void
	print_charbox(char *charbox_name, t_charbox *charbox)
{
	int	i;
	t_charbox *current;

	i = 0;
	current = charbox;
	dprintf(2, "<%s>\n", charbox_name);
	while (current)
	{
		dprintf(2, "    %03d data=|%s|, type=%d\n", i,
				current->data, current->type);
		current = current->next;
		i++;
	}
}

void
	print_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	dprintf(2, "-------------------\n");
	dprintf(2, "%-15s: %s\n", "rawcmd", cmd->rawcmd);
	print_charbox("io", cmd->io);
	print_charbox("argv", cmd->argv);
	print_charbox("theredoc", cmd->theredoc);
	print_charbox("last_input", cmd->last_input);
	print_charbox("last_output", cmd->last_output);
	dprintf(2, "%-15s: %d\n", "input_fd", cmd->input_fd);
	dprintf(2, "%-15s: %d\n", "output_fd", cmd->output_fd);
	dprintf(2, "%-15s: %d\n", "pipe_fd[0]", cmd->pipe_fd[0]);
	dprintf(2, "%-15s: %d\n", "pipe_fd[1]", cmd->pipe_fd[1]);
	dprintf(2, "%-15s: %d\n", "pid", cmd->pid);
}
