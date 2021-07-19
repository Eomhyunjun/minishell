/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 14:06:52 by heom              #+#    #+#             */
/*   Updated: 2021/07/19 16:42:21 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

void
	fork_loop(void)
{
	t_cmd	*current;

	current = all()->cmd_info;
	while (current)
	{
		current->pid = fork();
		if (current->pid == -1)
			safe_exit(1, "fork error!\n");
		if (current->pid == 0)
			do_child(current);
		current = current->next;
	}
}
