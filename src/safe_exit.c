/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 20:02:09 by heom              #+#    #+#             */
/*   Updated: 2021/06/22 20:15:52 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

void
	safe_cmd_free(void)
{
	t_cmd	*current;
	t_cmd	*removing;

	current = all()->cmd;
	while (current)
	{
		removing = current;
		current = current->next;
		if (removing->rawcmd)
			free(removing->rawcmd);
		free(removing);
	}
	all()->cmd = 0;
}

void
	safe_exit(int code, char *msg)
{
	safe_cmd_free();
	if (code != 0 && msg && msg[0])
		printf("%s\n", msg);
	exit(code);
}
