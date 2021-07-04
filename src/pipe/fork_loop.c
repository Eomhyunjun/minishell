/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 14:06:52 by heom              #+#    #+#             */
/*   Updated: 2021/07/04 16:14:30 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

int
	check_cmd(char *cmd)
{
	while (*cmd)
	{
		if (*cmd == '/')
			return (0);
		cmd++;
	}
	return (1);
}

char
	*try_execve_loop(t_cmd *current)
{
	char	*exec_path;
	char	**new_argv;
	int		i;

	// if (!(check_cmd(current->argv->data)))
	// 	return ("Invalid command");
	i = 0;
	while (all()->path[i])
	{
		exec_path = ft_strjoin(all()->path[i], "/", current->argv->data);
		new_argv = to_double_ptr(current->argv);
		execve(exec_path, new_argv, all()->dup_envp);
		free_char_double_ptr(new_argv);
		i++;
	}
	return ("Invalid command");
}

void
	do_child(t_cmd *current)
{
	char	*msg;

	//input
	if (current->last_input == NULL && current->prev != NULL)
		dup2(current->pipe_fd[0], STDIN_FILENO);
	else if (current->last_input != NULL && current->last_input->type == RD_I)
		dup2(current->input_fd, STDIN_FILENO);

	//output
	if (current->last_output == NULL && current->next != NULL)
		dup2(current->next->pipe_fd[1], STDOUT_FILENO);
	else if (current->last_output != NULL)
		dup2(current->output_fd, STDOUT_FILENO);
	close_unused();
	msg = try_execve_loop(current);
	safe_exit(1, msg);
}

void
	fork_loop(void)
{
	t_cmd	*current;

	current = all()->cmd_info;
	while (current)
	{

		current->pid = fork();
		if (current->pid == -1)
			safe_exit(1, "fork error!\n");
		if (current->pid == 0)
			do_child(current);
		current = current->next;
	}
}
