/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_exit_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 13:44:13 by heom              #+#    #+#             */
/*   Updated: 2021/07/16 15:14:21 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

void
	process_exit_pipe(void)
{
	char buf[2];
	int	read_len;

	read_len = 1;
	ft_bzero(buf, 2);
	while (1)
	{
		read_len = read(all()->exit_pipe[0], buf, sizeof(buf));
		if (read_len == 0)
			break ;
		if (read_len == -1)
			safe_exit(1, "env pipe read error");
		read(all()->exit_pipe[0], buf, 2);
		if (buf[0] == 'e')
			safe_exit(0, NULL);
		if (buf[0] == 'n')
			safe_exit(1, "numeric argument required");
		if (buf[0] == 'm')
			write(1, "too many arguments", 19);
	}
	close(all()->exit_pipe[0]);
}
