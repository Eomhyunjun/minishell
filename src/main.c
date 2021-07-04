/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 14:19:09 by heom              #+#    #+#             */
/*   Updated: 2021/07/04 16:13:12 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "egginshell.h"

void
	close_unused(void)
{
	t_cmd	*first_cmd;

	first_cmd = all()->cmd_info;
	while (first_cmd)
	{
		close(first_cmd->pipe_fd[0]);
		close(first_cmd->pipe_fd[1]);
		if (first_cmd->input_fd > 2)
			close(first_cmd->input_fd);
		if (first_cmd->output_fd > 2)
			close(first_cmd->output_fd);
		first_cmd = first_cmd->next;
	}
}

void
	wait_subprocess(void)
{
	t_cmd	*current;
	int		res;

	current = all()->cmd_info;
	while (current)
	{

		if (waitpid(current->pid, &res, 0) == -1)
			safe_exit(1, "waitpid error");
		print_cmd(current);
		current = current->next;
	}
}

int		main(int argc, char **argv, char **envp)
{
	(void)	argc;
	(void)	argv;
	char	*buf;

	// init(envp);
	// while ((buf = readline("egg > ")) != 0)
	// {
	// 	if (ft_strlen(buf) > 0)
	// 	{
	// 		add_history(buf);
	// 		printf("start hello world!\n");
	// 		// dprintf(2, "buf: %s\n", buf);
	// 		parse(buf);
	// 		make_io();
	// 		make_pipe();
	// 		fork_loop();
	// 		printf("end hello world!\n");
	// 	}
	// 	free(buf);
	// }
	init(envp);

	buf = "< b cat | cat > c";
	// printf("start hello world!\n");
	// dprintf(2, "buf: %s\n", buf);
	parse(buf);
	make_io();
	make_pipe();
	fork_loop();
	// printf("end hello world!\n");

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
	close_unused();
	wait_subprocess();
	safe_exit(0, NULL);
	return (0);
}


