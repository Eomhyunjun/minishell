/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehokim <taehokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 12:55:38 by taehokim          #+#    #+#             */
/*   Updated: 2021/07/18 18:52:00 by taehokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "egginshell.h"

int
	cd_send_path(t_cmd *cmd)
{
	char		*path;
	int			arg_len;

	arg_len = charbox_len(cmd->argv);
	if (arg_len == 1)
	{
		path = create_from_env("HOME");
		if (!path)
		{
			ft_putstr_plus_newline(2, "egginshell: cd: HOME not set");
			return (1);
		}
		write(all()->other_pipe[1], path, ft_strlen(path) + 1);
		free(path);
	}
	else
	{
		path = cmd->argv->next->data;
		write(all()->other_pipe[1], path, ft_strlen(path) + 1);
	}
	return (0);
}

int
	egg_cd(t_cmd *cmd)
{
	int			arg_len;
	char		inst[2];

	arg_len = charbox_len(cmd->argv);
	if (arg_len >= 3)
	{
		ft_putstr_plus_newline(2, "egginshell: cd: too many arguments");
		return (1);
	}
	inst[0] = OTHER_CD;
	inst[1] = '\0';
	write(all()->other_pipe[1], inst, 2);
	return (cd_send_path(cmd));
}
