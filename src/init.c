/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 15:21:31 by heom              #+#    #+#             */
/*   Updated: 2021/07/08 20:34:14 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			safe_exit(0, NULL);
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

void	init(char **envp)
{
	all()->dup_envp = envp;
	all()->path = get_path();
	tcgetattr(0, &all()->oldtio);
	getcwd(all()->pwd, PATH_MAX);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, do_nothing);
	rl_getc_function = custom_rl_getc_fuction;
	rl_catch_signals = 0;
}
