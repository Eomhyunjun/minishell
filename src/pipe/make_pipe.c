/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehokim <taehokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 14:00:58 by heom              #+#    #+#             */
/*   Updated: 2021/07/18 15:35:23 by taehokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

void
	make_pipe(void)
{
	t_cmd	*current;

	current = all()->cmd_info;
	while (current)
	{
		if (pipe(current->pipe_fd) || pipe(current->ii_fd))
			safe_exit(1, "pipe error!\n");
		current = current->next;
	}
	if (pipe(all()->env_pipe))
		safe_exit(1, "env_pipe error!\n");
	if (pipe(all()->exit_pipe))
		safe_exit(1, "exit_pipe error!\n");
	if (pipe(all()->other_pipe))
		safe_exit(1, "exit_pipe error!\n");
}
