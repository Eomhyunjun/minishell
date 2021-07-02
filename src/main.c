/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 14:19:09 by heom              #+#    #+#             */
/*   Updated: 2021/07/02 18:24:10 by heom             ###   ########.fr       */
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
			free_charbox(tmp_doc);
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
				// 이전 output_fd close 해줘야 함. -> 했음
				close(current->output_fd);
				current->output_fd = open(cur_io->data, O_RDWR | O_CREAT | O_APPEND, 0644); // 에러 처리 해야 함. 안했음
				current->last_output = cur_io;
			}
			else
			{
				// 이전 output_fd close 해줘야 함. -> 했음
				close(current->output_fd);
				current->output_fd = open(cur_io->data, O_RDWR | O_CREAT, 0644); // 에러 처리 해야 함. 안했음
				current->last_output = cur_io;
			}
			cur_io = cur_io->next;
		}
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
	//char *buf = "echo < a   ayo \"$A\"   <<  mmm  bb\"b   \"c  d nnn   >  bb xxx>ccc |>>dddd ss";
	char *buf = "<a echo >b";
	init(envp);
	parse(buf);
	make_io();
	make_pipe();
	fork_loop();

	//have to be removed
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


