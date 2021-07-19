/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   else_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 16:42:10 by heom              #+#    #+#             */
/*   Updated: 2021/07/19 20:36:57 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

void
	exec_path_cmd(t_cmd *current, t_exec *t)
{
	while (all()->path[t->i])
	{
		t->exec_path = ft_strjoin3(all()->path[t->i], "/", current->argv->data);
		execve(t->exec_path, t->argv_matrix, t->envp_matrix);
		free(t->exec_path);
		t->i++;
	}
	t->msg = ft_strjoin3("egginshell: ", current->argv->data,
			": command not found");
	ft_putstr_plus_newline(2, t->msg);
	free(t->msg);
	t->ret = 127;
}
