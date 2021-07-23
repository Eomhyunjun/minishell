/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 15:21:31 by heom              #+#    #+#             */
/*   Updated: 2021/07/23 14:44:58 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"
#ifdef __APPLE__
int
	custom_rl_getc_fuction(FILE *stream)
{
	int				result;
	unsigned char	c;

	(void)stream;
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
			return (EOF);
	}
}

#else
int
	custom_rl_getc_fuction(FILE *stream)
{
	int				result;
	unsigned char	c;

	(void)stream;
	while (1)
	{
		result = read(rl_instream->_fileno, &c, sizeof(unsigned char));
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

#endif

void
	sigint_handler(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void
	do_nothing(int signo)
{
	(void)signo;
}
