/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 14:19:09 by heom              #+#    #+#             */
/*   Updated: 2021/07/01 20:18:19 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "egginshell.h"

void	make_heredoc(t_cmd *current, t_charbox *cur_io)
{
	char		*buf;
	char		*merge;
	t_charbox	*tmp_doc;

	while ((buf = readline("theredoc>")))
	{
		if (buf[0] != '\0')
			add_history(buf);
		if (!ft_strcmp(buf, cur_io->data))
		{
			merge = to_chars(tmp_doc, "\n");
			add_charbox(&current->theredoc, merge, -2);
			safe_charbox_free(tmp_doc);
			break;
		}
		add_charbox(&tmp_doc, buf, 0);
	}
}

void	process_heredoc(void)
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
void	process_rd(void)
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
			if (cur_io->type == RD_II)
			{
				current->last_input = cur_theredoc;
				cur_theredoc = cur_theredoc->next;
			}
			else if (cur_io->type == RD_I)
			{
				if (current->input_fd != -1)
					close(current->input_fd);
				try_open_for_read(&current->input_fd, cur_io->data);
				current->last_input = cur_io;
			}
			else if (cur_io->type == RD_OO)
			{
				current->output_fd = open(cur_io->data, O_RDWR | O_CREAT, 0644);
				current->last_output = cur_io;
			}
			else
			{
				current->output_fd = open(cur_io->data, O_RDWR | O_CREAT, 0644);
				current->last_output = cur_io;
			}
			cur_io = cur_io->next;
		}
		if (current->last_input->type == '-2')
			current->input_fd = -1;
		current = current->next;
	}
}

void	make_io(void)
{
	process_heredoc();
	process_rd();
}

int		main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	char *buf = "kkk < 1abc   lll \"$A\"   <<  mmm  bb\"b   \"c  d nnn   >  asdfds xxx>zzz |>>sdf ss";

	init(envp);
	parse(buf);
	make_io();
	t_cmd *cmd;
	cmd = all()->cmd_info;
	while (cmd)
	{

		printf("--------\ncmd: %s\n", cmd->rawcmd);
		t_charbox *charbox;
		charbox = cmd->io;
		while (charbox)
		{
			printf("io type : %d, s : |%s|\n", charbox->type, charbox->data);
			charbox = charbox->next;
		}
		charbox = cmd->argv;
		while (charbox)
		{
			printf("argv type : %d, s : |%s|\n", charbox->type, charbox->data);
			charbox = charbox->next;
		}
		cmd = cmd->next;
	}
	safe_exit(0, NULL);
	return (0);
}


