/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_open.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 19:04:52 by heom              #+#    #+#             */
/*   Updated: 2021/07/04 20:12:58 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <errno.h>
#include "egginshell.h"

int
	try_open(int *fd, char *path, int mode, int permission)
{
	if (permission == 0)
		*fd = open(path, mode);
	else
		*fd = open(path, mode, permission);
	if (*fd == -1)
	{
		ft_putstr(2, "egginshell: ");
		ft_putstr(2, path);
		ft_putstr(2, ": ");
		ft_putstr(2, strerror(errno));
		ft_putstr(2, "\n");
		return (1);
	}
	return (0);
}

