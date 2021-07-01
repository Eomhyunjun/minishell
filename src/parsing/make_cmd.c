/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 15:22:35 by heom              #+#    #+#             */
/*   Updated: 2021/07/01 14:52:35 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

void	make_cmd_item(t_cmd *current)
{
	int		quote;
	int		i;

	i = 0;
	quote = Q_NONE;
	while (current->rawcmd[i])
	{
		if (!is_quote(current->rawcmd[i], &quote))
		{
			i = io_try_push(current, i); // only io exit error
			i = argv_try_push(current, i);
		}
	}
}

void	make_cmd(void)
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

void	make_rawcmd(char *buf)
{
	int	i;
	int cmd_start;
	int	quote;

	i = 0;
	quote = Q_NONE;
	cmd_start = 0;
	while (buf[i])
	{
		if (!is_quote(buf[i], &quote) && buf[i] == '|')
		{
			add_cmd(egg_strndup(buf, cmd_start, i - 1));
			cmd_start = i + 1;
		}
		i++;
	}
	add_cmd(egg_strndup(buf, cmd_start, i - 1));
	// should check if quote is open
	// should check if only one pipe end
}
