/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehokim <taehokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 14:06:52 by heom              #+#    #+#             */
/*   Updated: 2021/07/19 15:32:06 by taehokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

int
	check_builtin_cmd(t_cmd *current)
{

	if (ft_strcmp(current->argv->data, "env") == 0)
		return (EGG_ENV);
	if (ft_strcmp(current->argv->data, "export") == 0)
		return (EGG_EXPORT);
	if (ft_strcmp(current->argv->data, "unset") == 0)
		return (EGG_UNSET);
	if (ft_strcmp(current->argv->data, "echo") == 0)
		return (EGG_ECHO);
	if (ft_strcmp(current->argv->data, "cd") == 0)
		return (EGG_CD);
	if (ft_strcmp(current->argv->data, "exit") == 0)
		return (EGG_EXIT);
	if (ft_strcmp(current->argv->data, "pwd") == 0)
		return (EGG_PWD);
	return (0);
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

int
	exec_builtin_cmd(t_cmd *current)
{
	int	type;

	close(all()->env_pipe[0]);
	close(all()->exit_pipe[0]);
	close(all()->other_pipe[0]);
	type = check_builtin_cmd(current);
	if (type == EGG_ENV)
		return (egg_env(current));
	if (type == EGG_EXPORT)
		return (egg_export(current));
	if (type == EGG_UNSET)
		return (egg_unset(current));
	if (type == EGG_EXIT)
		return (egg_exit(current));
	if (type == EGG_ECHO)
		return (egg_echo(current));
	if (type == EGG_CD)
		return (egg_cd(current));
	if (type == EGG_PWD)
		return (egg_pwd());
	return (type);
}

int
	try_execve(t_cmd *current)
{
	char		*exec_path;
	char		**argv_matrix;
	char		**envp_matrix;
	char		*msg;
	int			i;
	int			ret;

	i = 0;
	ret = 0;
	argv_matrix = to_double_ptr(current->argv, NO_EXCLUDE);
	envp_matrix = to_double_ptr(all()->egg_envp, ENVTYPE_NULL);
	if (check_dir(current))
	{
		exec_path = ft_strjoin3(all()->pwd, "/", current->argv->data);
		execve(exec_path, argv_matrix, envp_matrix);
		free(exec_path);
		msg = ft_strjoin4("egginshell: ", argv_matrix[0], ": ", strerror(errno));
		ft_putstr_plus_newline(2, msg);
		free(msg);
	}
	// export, env, cd, echo, exit, pwd, unset
	else if (check_builtin_cmd(current))
		ret = exec_builtin_cmd(current);
	else
	{
		while (all()->path[i])
		{

			exec_path = ft_strjoin3(all()->path[i], "/", current->argv->data);
			execve(exec_path, argv_matrix, envp_matrix);
			free(exec_path);
			i++;
		}
		msg = ft_strjoin3("egginshell: ", current->argv->data,
			": command not found");
		ft_putstr_plus_newline(2, msg);
		free(msg);
		free_char_double_ptr(argv_matrix);
		ret = 127;
	}
	return (ret);
}

void
	do_child(t_cmd *current)
{
	int ret;
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
