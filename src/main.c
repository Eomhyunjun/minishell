/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 14:19:09 by heom              #+#    #+#             */
/*   Updated: 2021/07/15 16:24:50 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "egginshell.h"

void	read_env_pipe()
{
	int		read_len;
	char	buf[1024];
	char	env_type;
	char	*env_name;
	char	*env_value;
	int		start;
	int		i;

	read_len = 0;
	ft_bzero(buf, 1024);
	while (1)
	{
		read_len = read(all()->env_pipe[0], buf, 1024);
		dprintf(2, "%d, %s\n", read_len, buf);
		if (read_len == 0)
			break ;
		if (read_len == -1)
			safe_exit(1, "env pipe read error");
		i = 0;
		while (i < 1024)
		{
			env_type = buf[i];
			i += 2;
			start = i;
			while (buf[i] != '\0')
				i++;
			env_name = egg_strndup(buf, start, i - 1);
			i++;
			start = i;
			if (env_type == ENV_NEW || env_type == ENV_EDIT)
			{
				while (buf[i] != '\0')
					i++;
				env_value = egg_strndup(buf, start, i - 1);
			}
			if (env_type == ENV_NEW && add_new_envp(env_name, env_value))
				safe_exit(1, "env new failed");
			else if (env_type == ENV_EDIT && edit_envp(env_name, env_value))
				safe_exit(1, "env edit failed");
			else
				break ;
			i++;
		}
	}
	close(all()->env_pipe[0]);
	close(all()->env_pipe[1]);
}

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
		read_env_pipe();
		free(buf);
	}
	safe_exit(0, NULL);
	return (0);
}
