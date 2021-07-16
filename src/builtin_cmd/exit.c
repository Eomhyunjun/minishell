/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 13:22:51 by heom              #+#    #+#             */
/*   Updated: 2021/07/16 15:08:44 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

static int
	is_num(char *num)
{
	while (*num)
	{
		if (*num < '0' || *num > '9')
			return (0);
		num++;
	}
	return (1);
}

int
	egg_exit(t_cmd *cmd)
{
	t_charbox	*arg;
	int			res;

	res = 0;
	arg = cmd->argv->next;
	if (!arg || (!(arg->next)))
	{
		write(1, "exit\n", 5);
		if (!arg || is_num(arg->data))
		{
			write(all()->exit_pipe[1], "e", 2);
			if (is_num(arg->data))
				res = ft_atoi(arg->data);
		}
		else if (!is_num(arg->data))
		{
			write(all()->exit_pipe[1], "n", 2);
			res = 255;
		}
	}
	else
	{
		write(all()->exit_pipe[1], "m", 2);
		res = 1;
	}
	close(all()->exit_pipe[1]);
	return (res);
}
