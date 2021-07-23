/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 15:22:35 by heom              #+#    #+#             */
/*   Updated: 2021/07/23 12:36:15 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

int
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
			if (io_try_push(current, &i))
				return (1);
			i = argv_try_push(current, i);
		}
	}
	return (0);
}

int
	make_cmd(void)
{
	t_cmd	*current;

	current = all()->cmd_info;
	while (current)
	{
		if (make_cmd_item(current))
			return (1);
		interpret_charbox(current->io);
		interpret_charbox(current->argv);
		current = current->next;
	}
	return (0);
}

int
	if_empty_error(char *contents, char *msg)
{
	if (is_empty(contents))
	{
		ft_putstr_plus_newline(2, msg);
		return (1);
	}
}

int
	make_rawcmd_loop(char *buf, int i, int *cmd_start, char **contents)
{
	*contents = egg_strndup(buf, *cmd_start, i - 1);
	if (if_empty_error(contents,
			"egginshell: syntax error near unexpected token '|'"))
		return (1);
	add_cmd(*contents);
	*cmd_start = i + 1;
	return (0);
}

int
	make_rawcmd(char *buf)
{
	int		i;
	int		cmd_start;
	int		quote;
	char	*contents;

	i = -1;
	quote = Q_NONE;
	cmd_start = 0;
	while (buf[++i])
		if (!is_quote(buf[i], &quote) && buf[i] == '|')
			if (make_rawcmd_loop(buf, i, &cmd_start, &contents))
				return (1);
	if (quote != Q_NONE)
	{
		ft_putstr_plus_newline(2, "egginshell: you should close quote");
		return (1);
	}
	contents = egg_strndup(buf, cmd_start, i - 1);
	if (if_empty_error(contents,
			"egginshell: you should write something after '|'"))
		return (1);
	add_cmd(contents);
	return (0);
}
