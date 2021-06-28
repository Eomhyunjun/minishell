/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_try_push.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 15:50:35 by heom              #+#    #+#             */
/*   Updated: 2021/06/28 18:46:26 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"


int		add_io(t_cmd *current, int type, int i)
{
	int		start;
	int		end;
	char	*dub_res;
	char	*rawcmd;

	i++;
	rawcmd = current->rawcmd;
	i = get_none_space_pos(rawcmd, i);
	start = i;
	i = get_none_name_pos(rawcmd, i);
	end = i - 1;
	dub_res = egg_strndup(rawcmd, start, end);
	if (dub_res[0] == '\0')
		token_error(rawcmd[i]);
	add_charbox(&current->io, dub_res, type);
	return (i);
}

int		io_try_push(t_cmd *current, int i)
{
	char	*rawcmd;

	rawcmd = current->rawcmd;
	i = get_none_space_pos(current->rawcmd, i);
	if (!rawcmd[i])
		return (i);
	if (rawcmd[i] == '<' && rawcmd[i + 1] != '<')
		i = add_io(current, RD_I, i);
	else if (rawcmd[i] == '<' && rawcmd[i + 1] == '<')
		i = add_io(current, RD_II, i + 1);
	else if (rawcmd[i] == '>' && rawcmd[i + 1] != '>')
		i = add_io(current, RD_O, i);
	else if (rawcmd[i] == '>' && rawcmd[i + 1] == '>')
		i = add_io(current, RD_OO, i + 1);
	return (i);
}
