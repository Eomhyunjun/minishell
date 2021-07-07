/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_open.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 19:04:52 by heom              #+#    #+#             */
/*   Updated: 2021/07/07 14:24:07 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <errno.h>
#include "egginshell.h"

int
	try_open(int *fd, char *path, int mode, int permission)
{
	char	*msg;
	char	*trash_can;

	if (permission == 0)
		*fd = open(path, mode);
	else
		*fd = open(path, mode, permission);
	if (*fd == -1)
	{
		msg = ft_strjoin3("egginshell: ", path, ": ");
		trash_can = msg;
		msg = ft_strjoin3(msg, strerror(errno), "\n");
		free(trash_can);
		ft_putstr_plus_newline(2, msg);
		free(msg);
		return (1);
	}
	return (0);
}
