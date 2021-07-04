/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 14:36:43 by taehokim          #+#    #+#             */
/*   Updated: 2021/07/04 16:40:51 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

int
	index_end_export(char *data, int i)
{
	if (data[i] >= '0' && data[i] <= '9')
		return (i);
	while ((data[i] >= 'a' && data[i] <= 'z')
		|| (data[i] >= 'A' && data[i] <= 'Z')
		|| (data[i] >= '0' && data[i] <= '9')
		|| (data[i] == '_'))
	{
		i++;
	}
	return (i - 1);
}

int
	create_search(char *data, int start, char **search)
{
	int		end;

	end = index_end_export(data, start);
	*search = egg_strndup(data, start, end);
	return (end);
}

char
	*create_blank(void)
{
	char	*blank;

	if (!ft_malloc(&blank, 1))
		safe_exit(1, "create blank failed");
	blank[0] = '\0';
	return (blank);
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
	char	*res;
	char	*search;
	int		i;
	int		end;

	i = 0;
	end = create_search(data, start, &search);
	if (!search[0])
		; // 어떻게 될지 몰라.
	while (all()->dup_envp[i])
	{
		res = replace_dollar(all()->dup_envp[i], search);
		if (res[0] != '\0')
		{
			*replaced = res;
			free(search);
			return (end);
		}
		free(res);
		i++;
	}
	*replaced = create_blank();
	free(search);
	return (end);
}
