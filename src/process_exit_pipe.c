/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_exit_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 13:44:13 by heom              #+#    #+#             */
/*   Updated: 2021/07/16 14:56:56 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

void
	process_exit_pipe(void)
{
	char buf[2];
	// int	read_len;

	// 무한대기 풀려고 했는데 안먹음 ㅠㅠ
	// if (!(read_len = read(all()->exit_pipe[0], buf, sizeof(buf))))
	// 	return ;
	read(all()->exit_pipe[0], buf, 2);
	if (buf[0] == 'e')
		safe_exit(0, NULL);
	if (buf[0] == 'n')
		safe_exit(1, "numeric argument required");
	if (buf[0] == 'm')
		safe_exit(1, "too many arguments");
}
