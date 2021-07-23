/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 14:36:43 by taehokim          #+#    #+#             */
/*   Updated: 2021/07/23 12:23:41 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

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
	process_no_search(char *data, int start, int end, char **replaced)
{
	if (data[start] == '?')
	{
		*replaced = ft_itoa(all()->last_cmd_result);
		return (end + 1);
	}
	*replaced = create_dollar();
	return (end);
}

int
	process_replace(t_charbox *current, char *search, char **replaced)
{
	char		*res;

	res = replace_dollar(current->data, search);
	if (res[0] != '\0')
	{
		*replaced = res;
		free(search);
		return (1);
	}
	free(res);
	return (0);
}

int
	make_dollar(char *data, int start, char **replaced)
{
	char		*search;
	int			end;
	t_charbox	*current;

	end = create_search(data, start, &search);
	if (!search[0])
	{
		free(search);
		return (process_no_search(data, start, end, replaced));
	}
	current = all()->egg_envp;
	while (current)
	{
		if (process_replace(current, search, replaced))
			return (end);
		current = current->next;
	}
	*replaced = create_blank();
	free(search);
	return (end);
}
