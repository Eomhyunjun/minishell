/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 14:06:52 by heom              #+#    #+#             */
/*   Updated: 2021/07/05 17:19:24 by heom             ###   ########.fr       */
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

void
	try_execve_loop(t_cmd *current)
{
	char	*exec_path;
	char	**new_argv;
	int		i;

	// todo: 경로가 왔을 경우 해당 경로의 프로그램을 실행해야 함.
	i = 0;
	new_argv = to_double_ptr(current->argv);
	while (all()->path[i])
	{
		exec_path = ft_strjoin(all()->path[i], "/", current->argv->data);
		execve(exec_path, new_argv, all()->dup_envp);
		i++;
	}
	free_char_double_ptr(new_argv);
}

void
	do_child(t_cmd *current)
{
	char	*msg;

	if (current->last_input == NULL && current->prev != NULL)
		dup2(current->pipe_fd[0], STDIN_FILENO);
	else if (current->last_input != NULL && current->last_input->type == RD_I)
		dup2(current->input_fd, STDIN_FILENO);
	if (current->last_output == NULL && current->next != NULL)
		dup2(current->next->pipe_fd[1], STDOUT_FILENO);
	else if (current->last_output != NULL)
		dup2(current->output_fd, STDOUT_FILENO);
	close_unused();
	try_execve_loop(current);
	msg = ft_strjoin("egginshell: ", current->argv->data,
			": command not found\n");
	ft_putstr(2, msg);
	free(msg);
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
