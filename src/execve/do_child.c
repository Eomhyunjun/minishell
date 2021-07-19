/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 16:37:34 by heom              #+#    #+#             */
/*   Updated: 2021/07/19 20:37:24 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

void
	do_child(t_cmd *current)
{
	int	ret;

	if (current->last_input == NULL && current->prev != NULL)
		dup2(current->pipe_fd[0], STDIN_FILENO);
	else if (current->last_input != NULL && current->last_input->type == RD_I)
		dup2(current->input_fd, STDIN_FILENO);
	else if (current->last_input != NULL && current->last_input->type == RD_II)
		dup2(current->ii_fd[0], STDIN_FILENO);
	if (current->last_output == NULL && current->next != NULL)
		dup2(current->next->pipe_fd[1], STDOUT_FILENO);
	else if (current->last_output != NULL)
		dup2(current->output_fd, STDOUT_FILENO);
	close_unused();
	ret = try_execve(current);
	safe_exit(ret, NULL);
}
