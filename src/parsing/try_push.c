/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_push.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 15:50:35 by heom              #+#    #+#             */
/*   Updated: 2021/07/23 12:44:23 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

int
	error_empty_io(char *dup_res, char *rawcmd, int *i)
{
	char	*msg;

	free(dup_res);
	if (rawcmd[*i] == '\0')
		msg = ft_strjoin3("syntax error near unexpected token ", \
		"'newline'", "");
	else
	{
		dup_res = egg_strndup(rawcmd, *i, *i);
		msg = ft_strjoin3("syntax error near unexpected token '", \
		dup_res, "'");
		free(dup_res);
	}
	ft_putstr_plus_newline(2, msg);
	free(msg);
	return (1);
}

int
	add_io(t_cmd *current, int type, int *i)
{
	int		start;
	int		end;
	char	*dup_res;
	char	*rawcmd;

	if (type == RD_I || type == RD_O)
		(*i) += 1;
	else
		(*i) += 2;
	rawcmd = current->rawcmd;
	*i = get_none_space_pos(rawcmd, *i);
	start = *i;
	*i = get_none_name_pos(rawcmd, *i);
	end = *i - 1;
	dup_res = egg_strndup(rawcmd, start, end);
	if (dup_res[0] == '\0')
		return (error_empty_io(dup_res, rawcmd, i));
	add_charbox(&current->io, dup_res, type);
	return (0);
}

int
	io_try_push(t_cmd *current, int *i)
{
	char	*rawcmd;
	int		res;

	rawcmd = current->rawcmd;
	res = 0;
	*i = get_none_space_pos(current->rawcmd, *i);
	if (!rawcmd[*i])
		return (res);
	if (rawcmd[*i] == '<' && rawcmd[*i + 1] != '<')
		res = add_io(current, RD_I, i);
	else if (rawcmd[*i] == '<' && rawcmd[*i + 1] == '<')
		res = add_io(current, RD_II, i);
	else if (rawcmd[*i] == '>' && rawcmd[*i + 1] != '>')
		res = add_io(current, RD_O, i);
	else if (rawcmd[*i] == '>' && rawcmd[*i + 1] == '>')
		res = add_io(current, RD_OO, i);
	return (res);
}

int
	argv_try_push(t_cmd *current, int i)
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
