/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_none_pos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 15:23:57 by heom              #+#    #+#             */
/*   Updated: 2021/06/25 16:36:46 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

int		get_none_name_pos(char *rawcmd, int i)
{
	while (rawcmd[i] != '|'
		&& rawcmd[i] != '<'
		&& rawcmd[i] != '>'
		&& rawcmd[i] != ' '
		&& rawcmd[i] != '\n'
		&& rawcmd[i] != '\0')
		i++;
	return (i);
}

int		get_none_space_pos(char *rawcmd, int i)
{
	while (rawcmd[i] == ' ')
		i++;
	return (i);
}
