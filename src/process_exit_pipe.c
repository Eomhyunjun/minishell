/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_exit_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehokim <taehokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 13:44:13 by heom              #+#    #+#             */
/*   Updated: 2021/07/18 15:46:19 by taehokim         ###   ########.fr       */
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
		read_len = read(all()->exit_pipe[0], buf, sizeof(buf)); // 이거 좀 이상함
		if (read_len == 0)
			break ;
		if (read_len == -1)
			safe_exit(1, "env pipe read error");
		read(all()->exit_pipe[0], buf, 2); // 왜 read 두번?
		if (buf[0] == 'e')
			safe_exit(0, NULL);
		if (buf[0] == 'n')
			safe_exit(1, "numeric argument required");
		if (buf[0] == 'm')
			write(1, "too many arguments", 19);
	}
	close(all()->exit_pipe[0]);
}
