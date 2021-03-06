/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 14:00:58 by heom              #+#    #+#             */
/*   Updated: 2021/07/19 19:33:53 by heom             ###   ########.fr       */
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
}
