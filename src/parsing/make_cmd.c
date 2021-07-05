/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 15:22:35 by heom              #+#    #+#             */
/*   Updated: 2021/07/05 17:20:28 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

int
	is_empty(char *content)
{
	int	i;

	i = 0;
	while (content[i] == ' ')
		i++;
	if (content[i] == '\0')
		return (1);
	return (0);
}

void
	make_cmd_item(t_cmd *current)
{
	int		quote;
	int		i;

	i = 0;
	quote = Q_NONE;
	while (current->rawcmd[i])
	{
		if (!is_quote(current->rawcmd[i], &quote))
		{
			i = io_try_push(current, i); // only one io exit --> error
			i = argv_try_push(current, i);
		}
	}
}

void
	make_cmd(void)
{
	t_cmd	*current;

	current = all()->cmd_info;
	while (current)
	{
		make_cmd_item(current);
		interpret_charbox(current->io);
		interpret_charbox(current->argv);
		current = current->next;
	}
}

int
	make_rawcmd(char *buf)
{
	int		i;
	int		cmd_start;
	int		quote;
	char	*contents;

	i = 0;
	quote = Q_NONE;
	cmd_start = 0;
	while (buf[i])
	{
		if (!is_quote(buf[i], &quote) && buf[i] == '|')
		{
			contents = egg_strndup(buf, cmd_start, i - 1);
			if (is_empty(contents))
			{
				ft_putstr(2, "egginshell: syntax error near unexpected token '|'\n");
				return (1);
			}
			add_cmd(contents);
			cmd_start = i + 1;
		}
		i++;
	}
	if (quote != Q_NONE)
	{
		ft_putstr(2, "egginshell: you should close quote\n");
		return (1);
	}
	contents = egg_strndup(buf, cmd_start, i - 1);
	if (is_empty(contents))
	{
		ft_putstr(2, "egginshell: you should write something after '|'\n");
		return (1);
	}
	add_cmd(contents);
	return (0);
	// should check if only one pipe end
}
