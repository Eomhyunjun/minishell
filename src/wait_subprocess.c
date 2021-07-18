/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_subprocess.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 15:38:05 by heom              #+#    #+#             */
/*   Updated: 2021/07/18 13:30:31 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

void
	wait_subprocess(void)
{
	t_cmd	*current;
	int		res;

	current = all()->cmd_info;
	while (current)
	{
		if (current->pid > 0 && waitpid(current->pid, &res, 0) == -1)
			safe_exit(1, "waitpid error");
		current = current->next;
	}
	all()->last_cmd_result = WEXITSTATUS(res);
}
