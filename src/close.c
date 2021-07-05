/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 15:40:28 by heom              #+#    #+#             */
/*   Updated: 2021/07/05 15:40:33 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

void
	close_unused(void)
{
	t_cmd	*first_cmd;

	first_cmd = all()->cmd_info;
	while (first_cmd)
	{
		if (first_cmd->pipe_fd[0])
			close(first_cmd->pipe_fd[0]);
		if (first_cmd->pipe_fd[1])
			close(first_cmd->pipe_fd[1]);
		if (first_cmd->input_fd > 2)
			close(first_cmd->input_fd);
		if (first_cmd->output_fd > 2)
			close(first_cmd->output_fd);
		first_cmd = first_cmd->next;
	}
}
