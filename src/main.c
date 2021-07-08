/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 14:19:09 by heom              #+#    #+#             */
/*   Updated: 2021/07/08 19:17:05 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "egginshell.h"

int custom_rl_getc_fuction(FILE *stream)
{
	int result;
	unsigned char c;
	(void)(stream);

	while (1)
	{
		result = read(rl_instream->_file, &c, sizeof(unsigned char));
		if (c == 4 && *rl_line_buffer == '\0')
		{
			rl_on_new_line();
			write(1, "exit\n", 5);
			exit(0);
		}

		if (result == sizeof(unsigned char))
			return (c);
		if (result == 0)
		{
			printf("result is 0\n");
			return (EOF);
		}
	}
}

void sigint_handler(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	if (!all()->cmd_info)
		rl_redisplay();
}

void do_nothing(int signo)
{
	(void)signo;
}

int		main(int argc, char **argv, char **envp)
{
	(void)	argc;
	(void)	argv;
	char	*buf;

	init(envp);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, do_nothing);
	rl_getc_function = custom_rl_getc_fuction;
	rl_catch_signals = 0;
	while (1)
	{
		safe_free_cmd();
		buf = readline("egg in ₩^_^₩ ");
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
				ii_write();
			}
		}
		close_unused();
		wait_subprocess();
		free(buf);
	}
	safe_exit(0, NULL);
	return (0);
}
