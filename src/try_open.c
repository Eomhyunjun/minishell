/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_open.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 19:04:52 by heom              #+#    #+#             */
/*   Updated: 2021/07/01 19:11:51 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "egginshell.h"

void	try_open_for_read(int *fd, char *path)
{
	*fd = open(path, O_RDONLY);
	if (*fd == -1)
		safe_exit(1, "open failed"); // should fix
}
