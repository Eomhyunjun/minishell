/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 10:49:52 by taehokim          #+#    #+#             */
/*   Updated: 2021/07/12 19:22:04 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

t_charbox
	*find_envp(char *name)
{
	t_charbox	*current;
	int			len;

	len = ft_strlen(name);
	current = all()->egg_envp;
	while (current)
	{
		if (ft_strncmp(name, current->data, len)
			&& (current->data[len] == '=' || current->data[len] == '\0'))
			return (current);
		current = current->next;
	}
	return (NULL);
}

int
	edit_envp(t_charbox *arg, char *name, char *value)
{
	free(arg->data);
	arg->data = ft_strjoin3(name, "=", value);
	if (!arg->data)
		return (1);
	return (0);
}

int
	add_new_envp(char *name, char *value)
{
	char	*data;

	if (value)
		data = ft_strjoin3(name, "=", value);
	else
		data = egg_strdup(name);
	if (data == NULL)
		return (1);
	add_charbox(&all()->egg_envp, data, 0);
	return (0);
}

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
					mem_ret = edit_envp(env, name, value);
				else if (!env)
					mem_ret = add_new_envp(name, value);
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
	print_charbox("envp", all()->egg_envp);
	return (ret);
}
