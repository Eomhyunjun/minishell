/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 15:22:35 by heom              #+#    #+#             */
/*   Updated: 2021/06/28 19:30:28 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

int		cmd_try_push(t_cmd *current, int i)
{
	char	*rawcmd;
	char	*dub_res;
	int		start;
	int		end;

	rawcmd = current->rawcmd;
	i = get_none_space_pos(rawcmd, i);
	if (!rawcmd[i])
		return (i);
	start = i;
	i = get_none_name_pos(rawcmd, i);
	end = i - 1;
	dub_res = egg_strndup(rawcmd, start, end);
	if (!dub_res[0])
		free(dub_res);
	else
		add_charbox(&current->argv, dub_res, 0);
	return (i);
}

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
