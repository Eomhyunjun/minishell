/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 16:37:34 by heom              #+#    #+#             */
/*   Updated: 2021/07/23 16:11:10 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

void
	restore_builtin_stdio(void)
{
	if (all()->builtin_stdout != 1)
		close(all()->builtin_stdout);
	if (all()->builtin_stdin != 0)
		close(all()->builtin_stdin);
	all()->builtin_stdout = 1;
	all()->builtin_stdin = 0;
}

void
	change_builtin_stdio(t_cmd *current)
{
	if (current->last_input == NULL && current->prev != NULL)
		all()->builtin_stdin = current->pipe_fd[0];
	else if (current->last_input != NULL && current->last_input->type == RD_I)
		all()->builtin_stdin = current->input_fd;
	else if (current->last_input != NULL && current->last_input->type == RD_II)
		all()->builtin_stdin = current->ii_fd[0];
	if (current->last_output == NULL && current->next != NULL)
		all()->builtin_stdout = current->next->pipe_fd[1];
	else if (current->last_output != NULL)
		all()->builtin_stdout = current->output_fd;
}

void
	change_stdio(t_cmd *current)
{
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
}

void
	do_child(t_cmd *current)
{
	int	ret;

	change_stdio(current);
	close_unused();
	ret = try_execve(current);
	safe_exit(ret, NULL);
}
