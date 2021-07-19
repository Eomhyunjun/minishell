/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 13:22:51 by heom              #+#    #+#             */
/*   Updated: 2021/07/19 19:54:16 by heom             ###   ########.fr       */
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
	int			arg_len;

	res = 0;
	arg_len = charbox_len(cmd->argv) - 1;
	arg = cmd->argv->next;
	if (arg_len == 0)
		safe_exit(0, "exit");
	else if (is_num(arg->data))
	{
		if (arg_len == 1)
			safe_exit(ft_atoi(arg->data), "exit");
		else
		{
			write(2, "too many arguments\n", 20);
			return (1);
		}
	}
	else
		safe_exit(255, "numeric argument required");
	return (0);
}
