/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 16:41:21 by heom              #+#    #+#             */
/*   Updated: 2021/07/19 20:37:11 by heom             ###   ########.fr       */
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
	exec_builtin_cmd(t_cmd *current)
{
	int	type;

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
	return (1);
}
