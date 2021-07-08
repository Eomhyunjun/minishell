/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 14:19:09 by heom              #+#    #+#             */
/*   Updated: 2021/07/08 19:23:06 by heom             ###   ########.fr       */
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
