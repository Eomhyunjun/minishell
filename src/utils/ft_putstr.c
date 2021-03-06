/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 13:34:31 by heom              #+#    #+#             */
/*   Updated: 2021/07/19 20:38:49 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

void
	ft_putstr_plus_newline(int fd, const char *s)
{
	int		i;
	char	*msg;

	i = ft_strlen(s);
	msg = ft_strjoin3(s, "", "\n");
	write(fd, msg, i + 1);
	free(msg);
}
