/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 16:22:10 by heom              #+#    #+#             */
/*   Updated: 2021/07/15 16:23:52 by heom             ###   ########.fr       */
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

int
	edit_envp(char *name, char *value)
{
	t_charbox	*arg;

	arg = find_envp(name);
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
