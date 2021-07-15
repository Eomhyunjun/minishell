/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 10:49:52 by taehokim          #+#    #+#             */
/*   Updated: 2021/07/15 16:23:25 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

void
	print_export_error(char *data)
{
	char	*msg;

	msg = ft_strjoin3("egginshell: export: '", data, "': not a valid identifier");
	ft_putstr_plus_newline(2, msg);
	free(msg);
}

int
	validate_export(char *data, char **name, char **value)
{
	int	i;
	int	len;

	len = ft_strlen(data);
	if (!can_be_first_env_name(data[0]))
	{
		print_export_error(data);
		return (1);
	}
	i = 1;
	while (data[i] && data[i] != '=')
	{
		if (!can_be_env_name(data[i]))
		{
			print_export_error(data);
			return (1);
		}
		i++;
	}
	*name = egg_strndup(data, 0, i - 1);
	if (data[i] == '\0')
		*value = NULL;
	else
		*value = egg_strndup(data, i + 1, len - 1);
	return (0);
}

int
	send_env_code(char type, char *name, char *value)
{
	char	*ret;
	int		i;
	int		j;
	int		len;

	len = ft_strlen(name) + ft_strlen(value) + 4;
	if (!ft_malloc(&ret, len))
		return (1);
	ret[0] = type;
	ret[1] = '\0';
	i = 0;
	j = 2;
	while (name[i])
		ret[j++] = name[i++];
	ret[j++] = '\0';
	if (value)
	{
		i = 0;
		while (value[i])
			ret[j++] = value[i++];
		ret[j] = '\0';
	}
	write(all()->env_pipe[1], ret, len);
	return (0);
}

int
	egg_export(t_cmd *cmd)
{
	t_charbox	*arg;
	t_charbox	*env;
	int			ret;
	int			mem_ret;
	char		*name;
	char		*value;

	ret = 0;
	mem_ret = 0;
	if (charbox_len(cmd->argv) > 1)
	{
		arg = cmd->argv->next;
		while (arg)
		{
			if (validate_export(arg->data, &name, &value))
				ret = 1;
			else
			{
				env = find_envp(name);
				if (env && value)
					mem_ret = send_env_code(ENV_EDIT, name, value);
				else if (!env)
					mem_ret = send_env_code(ENV_NEW, name, value);
			}
			if (mem_ret == 1)
			{
				//메모리 에러 출력
				return (1);
			}
			arg = arg->next;
		}
	}
	else
	{
		// 있던 거 출력
	}
	// free(name);
	// if
	// free(value);
	print_charbox("envp", all()->egg_envp);
	return (ret);
}
