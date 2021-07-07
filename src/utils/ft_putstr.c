/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 13:34:31 by heom              #+#    #+#             */
/*   Updated: 2021/07/07 14:29:44 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

void
	ft_putstr_plus_newline(int fd, const char *s)
{
	int i;
	char *msg;

	i = ft_strlen(s);
	msg = ft_strjoin3(s, "", "\n");
	write(fd, msg, i + 1);
	free(msg);
}
