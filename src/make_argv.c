/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 15:22:35 by heom              #+#    #+#             */
/*   Updated: 2021/06/29 20:39:07 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

void	make_argv_item(t_cmd *current)
{
	int		quote;
	int		i;

	i = 0;
	quote = Q_NONE;
	while (current->rawcmd[i])
	{
		if (!is_quote(current->rawcmd[i], &quote))
		{
			i = io_try_push(current, i); // only io exit error
			i = cmd_try_push(current, i);
		}
	}
}

void	make_argv(void)
{
	t_cmd	*current;

	current = all()->cmd_info;
	while (current)
	{
		make_argv_item(current);
		interpret_quote_env(current);
		current = current->next;
	}
}
