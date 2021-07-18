/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehokim <taehokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 12:55:38 by taehokim          #+#    #+#             */
/*   Updated: 2021/07/18 13:33:02 by taehokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "egginshell.h"

int
	egg_cd(t_cmd *cmd)
{
	t_charbox	*args;
	t_charbox	*home;
	int			arg_len;

	args = cmd->argv->next;
	arg_len = charbox_len(cmd->argv);
	if (arg_len >= 3)
	{
		ft_putstr_plus_newline(2, "egginshell: cd: too many arguments");
		return (1);
	}
	if (arg_len == 1)
	{
		home = find_envp("HOME");
		if (!home)
		{
			ft_putstr_plus_newline(2, "egginshell: cd: HOME not set");
			return (1);
		}
		fstat
		chdir(home->data);
	}
	return (0);
}
