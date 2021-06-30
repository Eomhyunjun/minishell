/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_none_pos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehokim <taehokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 15:23:57 by heom              #+#    #+#             */
/*   Updated: 2021/06/30 16:34:58 by taehokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

int		get_none_name_pos(char *rawcmd, int i)
{
	int		quote;

	quote = Q_NONE;
	while (
		(is_quote(rawcmd[i], &quote) != 0)
		|| (rawcmd[i] != '|'
		&& rawcmd[i] != '<'
		&& rawcmd[i] != '>'
		&& rawcmd[i] != ' '
		&& rawcmd[i] != '\n'
		&& rawcmd[i] != '\0')
		)
		i++;
	return (i);
}

int		get_none_space_pos(char *rawcmd, int i)
{
	while (rawcmd[i] == ' ')
		i++;
	return (i);
}
