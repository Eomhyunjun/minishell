/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 14:19:09 by heom              #+#    #+#             */
/*   Updated: 2021/06/29 15:23:06 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

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


void	parse(char *buf)
{
	make_rawcmd(buf);
	make_argv();
}

int		main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	char *buf = "kkk < 1abc   lll \"$A\"   <<  mmm  bb\"b   \"c  d nnn   >  asdfds xxx>zzz |>>sdf ss";

	init(envp);
	parse(buf);
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


