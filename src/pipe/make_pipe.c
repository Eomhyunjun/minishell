/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 14:00:58 by heom              #+#    #+#             */
/*   Updated: 2021/07/07 15:56:38 by heom             ###   ########.fr       */
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
