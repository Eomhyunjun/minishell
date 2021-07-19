/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 16:38:47 by heom              #+#    #+#             */
/*   Updated: 2021/07/19 20:37:57 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

t_exec
	init_try_execve_vars(t_cmd *current)
{
	t_exec	t;

	t.i = 0;
	t.ret = 1;
	t.argv_matrix = to_double_ptr(current->argv, NO_EXCLUDE);
	t.envp_matrix = to_double_ptr(all()->egg_envp, ENVTYPE_NULL);
	t.cwd = getcwd(NULL, 0);
	return (t);
}

void
	free_execve_vars(t_exec	t)
{
	free(t.cwd);
	free_char_double_ptr(t.argv_matrix);
	free_char_double_ptr(t.envp_matrix);
}

int
	try_execve(t_cmd *current)
{
	t_exec	t;

	t = init_try_execve_vars(current);
	if (check_dir(current))
		exec_dir_cmd(current, &t);
	else if (check_builtin_cmd(current))
		t.ret = exec_builtin_cmd(current);
	else
		exec_path_cmd(current, &t);
	free_execve_vars(t);
	return (t.ret);
}
