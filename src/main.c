/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 14:19:09 by heom              #+#    #+#             */
/*   Updated: 2021/07/16 13:48:40 by heom             ###   ########.fr       */
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
		if (ft_strlen(buf) > 0 && !is_empty(buf))
		{
			add_history(buf);
			if (!parse(buf) && !make_io())
			{
				make_pipe();
				fork_loop();
				ii_write();
			}
		}
		close_unused();
		close(all()->env_pipe[1]);
		wait_subprocess();
		process_env_pipe();
		process_exit_pipe();
		// print_charbox("envp", all()->egg_envp);
		free(buf);
	}
	safe_exit(0, NULL);
	return (0);
}
