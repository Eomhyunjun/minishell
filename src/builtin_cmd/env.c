/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 15:27:43 by heom              #+#    #+#             */
/*   Updated: 2021/07/23 16:49:31 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

void
	print_env_error(char *data)
{
	char	*msg;

	msg = ft_strjoin3("env: ", data, ": No such file or directory");
	ft_putstr_plus_newline(2, msg);
	free(msg);
}

int
	egg_env(t_cmd *cur_cmd)
{
	t_charbox	*cur_env;
	t_charbox	*cur_arg;

	cur_arg = cur_cmd->argv;
	if (cur_arg->next != NULL)
	{
		print_env_error(cur_arg->next->data);
		return (127);
	}
	cur_env = all()->egg_envp;
	while (cur_env)
	{
		if (cur_env->type == ENVTYPE_STR)
			ft_putstr_plus_newline(all()->builtin_stdout, cur_env->data);
		cur_env = cur_env->next;
	}
	return (0);
}
