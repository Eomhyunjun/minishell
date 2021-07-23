/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_subprocess.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 15:38:05 by heom              #+#    #+#             */
/*   Updated: 2021/07/23 15:05:13 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "egginshell.h"

void
	wait_subprocess(void)
{
	t_cmd	*current;
	int		res;
	int		sig_num;

	sig_num = 0;
	current = all()->cmd_info;
	while (current)
	{
		if (current->pid > 0 && waitpid(current->pid, &res, 0) == -1)
			safe_exit(1, "waitpid error");
		if (WTERMSIG(res) == SIGINT || WTERMSIG(res) == SIGQUIT)
			sig_num = WTERMSIG(res);
		current = current->next;
	}
	all()->last_cmd_result = WEXITSTATUS(res);
	if (sig_num == SIGINT)
		write(1, "\n", 1);
	else if (sig_num == SIGQUIT)
		write(1, "QUIT: 3\n", 8);
}
