/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 13:34:31 by heom              #+#    #+#             */
/*   Updated: 2021/07/04 19:44:13 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void
	ft_putstr(int fd, const char *s)
{
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}
