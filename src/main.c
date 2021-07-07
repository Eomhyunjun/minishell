/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 14:19:09 by heom              #+#    #+#             */
/*   Updated: 2021/07/07 09:12:31 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "egginshell.h"

int		main(int argc, char **argv, char **envp)
{
	(void)	argc;
	(void)	argv;
	char	*buf;

	init(envp);
	while (1)
	{
		buf = readline("egg > ");
		dprintf(2, "buf: %s\n", buf);
		if (buf == 0)
			break;
		if (ft_strlen(buf) > 0)
		{
			safe_free_cmd();
			add_history(buf);
			if (!parse(buf) && !make_io())
			{
				make_pipe();
				fork_loop();
			}
		}
		close_unused();
		wait_subprocess();
		free(buf);
	}
	// init(envp);

	// buf = "< 123d cat";
	// dprintf(2, "buf: %s\n", buf);
	// parse(buf);
	// make_io();
	// make_pipe();
	// fork_loop();

	//have to be removed
	// t_cmd *cmd;
	// cmd = all()->cmd_info;
	// while (cmd)
	// {

	// 	printf("--------\ncmd: %s\n", cmd->rawcmd);
	// 	t_charbox *charbox;
	// 	charbox = cmd->io;
	// 	while (charbox)
	// 	{
	// 		printf("io type : %d, s : |%s|\n", charbox->type, charbox->data);
	// 		charbox = charbox->next;
	// 	}
	// 	charbox = cmd->argv;
	// 	while (charbox)
	// 	{
	// 		printf("argv type : %d, s : |%s|\n", charbox->type, charbox->data);
	// 		charbox = charbox->next;
	// 	}
	// 	cmd = cmd->next;
	// }
	safe_exit(0, NULL);
	return (0);
}


