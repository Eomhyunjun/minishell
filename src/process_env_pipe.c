/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_env_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 19:33:35 by heom              #+#    #+#             */
/*   Updated: 2021/07/16 15:07:01 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

void	process_env_pipe(void)
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
		if (read_len == 0)
			break ;
		if (read_len == -1)
			safe_exit(1, "env pipe read error");
		i = 0;
		while (i < read_len)
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
			//dprintf(2, "type : %c, name : %s, value : %s\n", env_type, env_name, env_value);
			if (env_type == ENV_NEW && add_new_envp(env_name, env_value))
				safe_exit(1, "env new failed");
			else if (env_type == ENV_EDIT && edit_envp(env_name, env_value))
				safe_exit(1, "env edit failed");
			else if (env_type == ENV_UNSET && unset_envp(env_name))
				safe_exit(1, "env unset failed");
			else if (env_type == ENV_NEW_NULL && !find_envp(env_name) && add_new_envp(env_name, NULL))
				safe_exit(1, "env new null failed");
			i++;
		}
	}
	close(all()->env_pipe[0]);
}
