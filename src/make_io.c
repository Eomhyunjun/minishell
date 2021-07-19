/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 14:15:45 by heom              #+#    #+#             */
/*   Updated: 2021/07/19 20:35:06 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "egginshell.h"

void
	make_heredoc(t_cmd *current, t_charbox *cur_io)
{
	char		*buf;
	char		*merge;
	t_charbox	*tmp_doc;

	tmp_doc = NULL;
	while (1)
	{
		buf = readline("theredoc > ");
		if (buf == NULL)
			break ;
		if (buf[0] != '\0')
			add_history(buf);
		if (!ft_strcmp(buf, cur_io->data))
		{
			merge = to_chars(tmp_doc, "\n");
			add_charbox(&current->theredoc, merge, RD_II);
			free_charbox(tmp_doc);
			break ;
		}
		add_charbox(&tmp_doc, buf, 0);
	}
}

void
	process_heredoc(void)
{
	t_cmd		*current;
	t_charbox	*cur_io;

	current = all()->cmd_info;
	while (current)
	{
		cur_io = current->io;
		while (cur_io)
		{
			if (cur_io->type == RD_II)
				make_heredoc(current, cur_io);
			cur_io = cur_io->next;
		}
		current = current->next;
	}
}

int
	process_rd(void)
{
	t_cmd		*current;
	t_charbox	*cur_io;
	t_charbox	*cur_theredoc;

	current = all()->cmd_info;
	while (current)
	{
		cur_io = current->io;
		cur_theredoc = current->theredoc;
		while (cur_io)
		{
			if (process_open(current, cur_io, cur_theredoc))
				return (1);
			cur_io = cur_io->next;
		}
		current = current->next;
	}
	return (0);
}

int
	make_io(void)
{
	process_heredoc();
	if (process_rd())
		return (1);
	return (0);
}
