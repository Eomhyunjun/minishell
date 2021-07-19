/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 16:40:30 by heom              #+#    #+#             */
/*   Updated: 2021/07/19 20:37:51 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

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
	exec_dir_cmd(t_cmd *current, t_exec *t)
{
	t->exec_path = ft_strjoin3(t->cwd, "/", current->argv->data);
	if (current->argv->data[0] == '/')
		execve(current->argv->data, t->argv_matrix, t->envp_matrix);
	else
		execve(t->exec_path, t->argv_matrix, t->envp_matrix);
	t->msg = ft_strjoin4("egginshell: ", t->argv_matrix[0],
			": ", strerror(errno));
	ft_putstr_plus_newline(2, t->msg);
	free(t->msg);
	free(t->exec_path);
	t->ret = 127;
}
