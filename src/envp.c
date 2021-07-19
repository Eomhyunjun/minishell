/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 16:22:10 by heom              #+#    #+#             */
/*   Updated: 2021/07/19 20:22:48 by heom             ###   ########.fr       */
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
		if (ft_strncmp(name, current->data, len) == 0
			&& (current->data[len] == '=' || current->data[len] == '\0'))
			return (current);
		current = current->next;
	}
	return (NULL);
}

char
	*create_from_env(char *name)
{
	t_charbox	*env;
	int			start;
	int			end;

	env = find_envp(name);
	if (!env || env->type == ENVTYPE_NULL)
		return (NULL);
	end = ft_strlen(env->data) - 1;
	start = 0;
	while (env->data[start] != '=')
	{
		start++;
	}
	start++;
	return (egg_strndup(env->data, start, end));
}

int
	edit_envp(char *name, char *value)
{
	t_charbox	*arg;

	arg = find_envp(name);
	free(arg->data);
	arg->data = ft_strjoin3(name, "=", value);
	arg->type = ENVTYPE_STR;
	if (!arg->data)
		return (1);
	return (0);
}

int
	add_new_envp(char *name, char *value)
{
	char	*data;
	int		type;

	if (value)
	{
		data = ft_strjoin3(name, "=", value);
		type = ENVTYPE_STR;
	}
	else
	{
		data = egg_strdup(name);
		type = ENVTYPE_NULL;
	}
	if (data == NULL)
		return (1);
	add_charbox(&all()->egg_envp, data, type);
	return (0);
}

int
	update_envp(char *name, char *value)
{
	int			mem_ret;
	t_charbox	*env;

	mem_ret = 0;
	env = find_envp(name);
	if (!env)
		mem_ret = add_new_envp(name, value);
	else if (value)
		mem_ret = edit_envp(name, value);
	return (mem_ret);
}
