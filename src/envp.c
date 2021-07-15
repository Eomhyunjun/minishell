/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 16:22:10 by heom              #+#    #+#             */
/*   Updated: 2021/07/15 19:50:57 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

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

int
	unset_envp(char *name)
{
	t_charbox	*arg;

	arg = find_envp(name);
	if (!arg)
		return (0);
	if (arg->prev)
		arg->prev->next = arg->next;
	if (arg->next)
		arg->next->prev = arg->prev;
	free(arg->data);
	free(arg);
	return (0);
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
