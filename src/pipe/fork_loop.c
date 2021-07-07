/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 14:06:52 by heom              #+#    #+#             */
/*   Updated: 2021/07/07 14:25:02 by heom             ###   ########.fr       */
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

int
	check_dir(t_cmd *current)
{
	int		i;
	char	*data;

	i = 0;
	data = current->argv->data;
	while (data[i])
	{
		if (data[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void
	try_execve(t_cmd *current)
{
	char	*exec_path;
	char	**new_argv;
	char	*msg;
	int		i;

	i = 0;
	new_argv = to_double_ptr(current->argv);
	if (check_dir(current))
	{
		exec_path = ft_strjoin3(all()->pwd, "/", current->argv->data);
		execve(exec_path, new_argv, all()->dup_envp);
		free(exec_path);
		msg = ft_strjoin4("egginshell: ", new_argv[0], ": ", strerror(errno));
		ft_putstr_plus_newline(2, msg);
		free(msg);
	}
	else
	{
		while (all()->path[i])
		{
			exec_path = ft_strjoin3(all()->path[i], "/", current->argv->data);
			execve(exec_path, new_argv, all()->dup_envp);
			free(exec_path);
			i++;
		}
		msg = ft_strjoin3("egginshell: ", current->argv->data,
			": command not found");
		ft_putstr_plus_newline(2, msg);
		free(msg);
	}
	free_char_double_ptr(new_argv);
}

void
	do_child(t_cmd *current)
{
	if (current->last_input == NULL && current->prev != NULL)
		dup2(current->pipe_fd[0], STDIN_FILENO);
	else if (current->last_input != NULL && current->last_input->type == RD_I)
		dup2(current->input_fd, STDIN_FILENO);
	if (current->last_output == NULL && current->next != NULL)
		dup2(current->next->pipe_fd[1], STDOUT_FILENO);
	else if (current->last_output != NULL)
		dup2(current->output_fd, STDOUT_FILENO);
	close_unused();
	try_execve(current);
	safe_exit(1, NULL);
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
