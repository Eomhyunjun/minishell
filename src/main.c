/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehokim <taehokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 14:19:09 by heom              #+#    #+#             */
/*   Updated: 2021/07/18 15:36:00 by taehokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "egginshell.h"

int		main(int argc, char **argv, char **envp)
{
	(void)	argc;
	(void)	argv;
	char	*buf;
	int		piped;

	init(envp);
	piped = 0;
	while (1)
	{
		safe_free_cmd();
		buf = readline("egg in ₩^_^₩ ");
		if (buf == 0)
			break;
		if (ft_strlen(buf) > 0 && !is_empty(buf))
		{
			add_history(buf);
			if (!parse(buf) && !make_io())
			{
				piped = 1;
				make_pipe();
				fork_loop();
				ii_write();
			}
		}
		close_unused();
		wait_subprocess();
		if (piped)
		{
			close(all()->env_pipe[1]);
			close(all()->exit_pipe[1]);
			close(all()->other_pipe[1]);
			process_env_pipe();
			process_exit_pipe();
			process_other_pipe();
		}
		free(buf);
	}
	safe_exit(0, NULL);
	return (0);
}
