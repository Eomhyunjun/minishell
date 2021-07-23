/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 14:19:09 by heom              #+#    #+#             */
/*   Updated: 2021/07/23 12:22:32 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "egginshell.h"

void	init(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		add_charbox(&all()->egg_envp, egg_strdup(envp[i]), 0);
		i++;
	}
	all()->path = get_path();
	tcgetattr(0, &all()->oldtio);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, do_nothing);
	rl_getc_function = custom_rl_getc_fuction;
	rl_catch_signals = 0;
}

void
	do_main_pro(char *buf)
{
	int	one_builtin;

	one_builtin = 0;
	if (ft_strlen(buf) > 0 && !is_empty(buf))
	{
		add_history(buf);
		if (!parse(buf) && !make_io())
		{
			one_builtin = !all()->cmd_info->next
				&& check_builtin_cmd(all()->cmd_info);
			if (one_builtin)
				all()->last_cmd_result = exec_builtin_cmd(all()->cmd_info);
			else
			{
				make_pipe();
				fork_loop();
				ii_write();
			}
		}
	}
	close_unused();
	if (!one_builtin)
		wait_subprocess();
}

int
	main(int argc, char **argv, char **envp)
{
	char	*buf;

	(void)argc;
	(void)argv;
	init(envp);
	while (1)
	{
		safe_free_cmd();
		buf = readline("egg in ₩^_^₩ ");
		if (buf == 0)
			break ;
		do_main_pro(buf);
		free(buf);
	}
	safe_exit(0, NULL);
	return (0);
}
