/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehokim <taehokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 14:19:09 by heom              #+#    #+#             */
/*   Updated: 2021/06/30 17:18:46 by taehokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

void	make_heredoc(t_cmd *current)
{
	char *buf;

	while ((buf = readline("theredoc>")))
	{
		if (buf[0] != '\0')
		{
			add_history(buf);
		}
		add_charbox(&current->theredoc, buf, 0); //need free
		if (buf[0] == 'H')
			break;
	}
}

void	make_io(void)
{
	t_cmd	*current;
	t_charbox	*cur_io;

	current = all()->cmd_info;
	while (current)
	{
		cur_io = current->io;
		while (cur_io)
		{
			if (cur_io->type == RD_II)
				make_heredoc(current);
			cur_io = cur_io->next;
		}
		// need remove
		t_charbox *Ayo;
		Ayo = current->theredoc;
		int i = 0;
		while (Ayo)
		{
			printf("%d buf : %s\n", i++, Ayo->data);
			Ayo = Ayo->next;
		}
		current = current->next;
	}
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


