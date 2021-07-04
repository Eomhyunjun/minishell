/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 14:06:52 by heom              #+#    #+#             */
/*   Updated: 2021/07/04 13:38:26 by heom             ###   ########.fr       */
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
	int		ret;
	char	*exec_path;
	char	**new_argv;
	int		i;

	ret = -1;
	if (!(check_cmd(current->argv->data)))
		return ("Invalid command");
	i = 0;
	while (ret == -1 && all()->path[i])
	{
		exec_path = ft_strjoin(all()->path[i], "/", current->argv->data);
		new_argv = to_double_ptr(current->argv);
		ret = execve(exec_path, new_argv, all()->dup_envp);
		free_char_double_ptr(new_argv);
		i++;
	}
	return ("Invalid command");
}

void
	do_child(t_cmd *current)
{
	char	*msg;
	t_cmd	*first_cmd;

	//input
	if (current->last_input == NULL && current->prev == NULL)
		dup2(current->pipe_fd[0], STDIN_FILENO);
	else if (current->last_input->type == RD_I)
		dup2(current->input_fd, STDIN_FILENO);

	//output
	if (current->last_output == NULL && current->next == NULL)
		dup2(current->next->pipe_fd[1], STDOUT_FILENO);
	else if (current->last_output != NULL)
		dup2(current->output_fd, STDOUT_FILENO);

	first_cmd = all()->cmd_info;
	while (first_cmd)
	{
		close(first_cmd->pipe_fd[0]);
		close(first_cmd->pipe_fd[1]);
		if (first_cmd->input_fd != -1)
			close(first_cmd->input_fd);
		if (first_cmd->output_fd != -1)
			close(first_cmd->output_fd);
		first_cmd = first_cmd->next;
	}
	msg = try_execve_loop(current);
	safe_exit(1, msg);
}

void
	fork_loop(void)
{
	int		i;
	t_cmd	*current;

	i = 0;
	current = all()->cmd_info;
	while (current)
	{
		current->pid = fork();
		if (current->pid == -1)
			safe_exit(1, "fork error!\n");
		if (current->pid == 0)
			do_child(current);
		i++;
	}
}
