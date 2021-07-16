/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 14:15:45 by heom              #+#    #+#             */
/*   Updated: 2021/07/16 15:36:08 by heom             ###   ########.fr       */
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
		//print_cmd(current);
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
	process_open(t_cmd *current, t_charbox *cur_io, t_charbox *cur_theredoc)
{
	int	mode;

	if (cur_io->type == RD_II)
	{
		current->last_input = cur_theredoc;
		cur_theredoc = cur_theredoc->next;
	}
	else if (cur_io->type == RD_I)
	{
		if (current->input_fd > 2)
			close(current->input_fd);
		if (try_open(&current->input_fd, cur_io->data, O_RDONLY, 0))
			return (1);
		current->last_input = cur_io;
	}
	else
	{
		if (cur_io->type == RD_OO)
			mode = O_RDWR | O_CREAT | O_APPEND;
		else
			mode = O_RDWR | O_CREAT | O_TRUNC;
		if (current->output_fd > 2)
			close(current->output_fd);
		if (try_open(&current->output_fd, cur_io->data, mode, 0644))
			return (1);
		current->last_output = cur_io;
	}
	return (0);
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
