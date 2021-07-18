/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 14:36:43 by taehokim          #+#    #+#             */
/*   Updated: 2021/07/18 13:30:22 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

int
	can_be_env_name(char c)
{
	return ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9')
		|| (c == '_'));
}

int
	can_be_first_env_name(char c)
{
	return ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c == '_'));
}

int
	create_search(char *data, int start, char **search)
{
	int		end;
	int		i;

	i = start;
	if (!can_be_first_env_name(data[i]))
		end = i - 1;
	else
	{
		while (can_be_env_name(data[i]))
			i++;
		end = i - 1;
	}
	*search = egg_strndup(data, start, end);
	return (end);
}

char
	*replace_dollar(char *env, char *search)
{
	int		env_end;
	int		search_len;

	env_end = 0;
	search_len = 0;
	while (search[search_len])
		search_len++;
	if (!(ft_strncmp(search, env, search_len)) && env[search_len] == '=')
	{
		while (env[env_end++])
			;
		return (egg_strndup(env, search_len + 1, env_end));
	}
	return (create_blank());
}

int
	make_dollar(char *data, int start, char **replaced)
{
	char		*res;
	char		*search;
	int			end;
	t_charbox	*current;

	end = create_search(data, start, &search);
	if (!search[0])
	{
		free(search);
		if (data[start] == '?')
		{
			*replaced = egg_strdup(ft_itoa(all()->last_cmd_result));
			return (end + 1);
		}
		*replaced = create_dollar();
		return (end);
	}
	current = all()->egg_envp;
	while (current)
	{
		res = replace_dollar(current->data, search);
		if (res[0] != '\0')
		{
			*replaced = res;
			free(search);
			return (end);
		}
		free(res);
		current = current->next;
	}
	*replaced = create_blank();
	free(search);
	return (end);
}
