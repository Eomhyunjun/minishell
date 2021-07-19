/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 12:55:38 by taehokim          #+#    #+#             */
/*   Updated: 2021/07/19 20:10:38 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "egginshell.h"

int
	try_chdir(char *path)
{
	char	*tmp;

	if (chdir(path))
	{
		tmp = ft_strjoin4("egginshell: cd: ", path, ": ", strerror(errno));
		ft_putstr_plus_newline(2, tmp);
		free(tmp);
		return (1);
	}
	tmp = getcwd(NULL, 0);
	if (edit_envp("PWD", tmp))
		safe_exit(1, "pwd memory error while cd");
	free(tmp);
	return (0);
}

int
	egg_cd_home(void)
{
	int		ret;
	char	*path;

	path = create_from_env("HOME");
	if (!path)
	{
		ft_putstr_plus_newline(2, "egginshell: cd: HOME not set");
		return (1);
	}
	ret = try_chdir(path);
	free(path);
	return (ret);
}

int
	egg_cd(t_cmd *cmd)
{
	int			arg_len;
	int			ret;
	char		*path;

	arg_len = charbox_len(cmd->argv);
	if (arg_len == 1)
		ret = egg_cd_home();
	else
	{
		path = cmd->argv->next->data;
		ret = try_chdir(path);
	}
	return (ret);
}
