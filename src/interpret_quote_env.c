/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_quote_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 19:30:34 by heom              #+#    #+#             */
/*   Updated: 2021/06/28 22:45:16 by heom             ###   ########.fr       */
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

	if (!(blank = malloc(1)))
		safe_exit(1, "create blank failed");
	blank[0] = '\0';
	return (blank);
}

char
	*replace_dollar(char *s, char *search)
{
	int		s_end;
	int		search_len;

	s_end = 0;
	search_len = 0;
	while (search[search_len])
		search_len++;
	if (!(ft_strncmp(search, s, search_len)) && s[search_len] == '=')
	{
		while (s[s_end++])
			;
		return (egg_strndup(s, search_len + 1, s_end));
	}
	return (create_blank());
}



int
	make_dollar(char *data, int start, char **replaced)
{
	char	*s;
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
		s = all()->dup_envp[i];
		res = replace_dollar(s, search);
		if (res[0] != '\0')
		{
			*replaced = res;
			return (end);
		}
		free(res);
		i++;
	}
	*replaced = create_blank();
	return (end);
}
char
	*interpret_quote_env_item(char *data)
{
	int start;
	int	i;
	int num;
	char *chars;
	t_charbox *box;
	char *res;
	int	quote;

	i = 0;
	start = 0;
	num = 0;
	quote = Q_NONE;
	box = NULL;
	while (data[i])
	{
		is_quote(data[i], &quote);
		if (data[i] == '$' || data[i] == '"' || data[i] == '\'')
		{
			if ((quote == Q_SINGLE && data[i] == '$')
				|| (quote == Q_DOUBLE && data[i] == '\'')
				|| (quote == Q_SINGLE && data[i] == '"'))
				;
			else
			{
				if (start <= i - 1)
				{
					chars = egg_strndup(data, start, i - 1);
					add_charbox(&box, chars, 0);
				}
				if (data[i] == '$')
				{
					i = make_dollar(data, i + 1, &chars);
					add_charbox(&box, chars, 0);
				}
				start = i + 1;
			}
		}
		i++;
	}
	chars = egg_strndup(data, start, i - 1);
	add_charbox(&box, chars, 0);

	// " 열린 채로 끝났을 때 에러 처리 필요함.
	res = to_chars(box);
	free(box); //more
	return (res);
}

void
	interpret_quote_env(t_cmd *cmd)
{
	t_charbox	*io;
	// t_charbox	*argv;

	io = cmd->io;
	while (io)
	{
		io->data = interpret_quote_env_item(io->data);
		io = io->next;
	}

	//

}
