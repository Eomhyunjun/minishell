/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   egg_strndup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 19:23:17 by heom              #+#    #+#             */
/*   Updated: 2021/07/02 16:12:10 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

char
	*egg_strdup(const char *s1)
{
	int	len;

	len = ft_strlen(s1);
	return (egg_strndup(s1, 0, len - 1));
}

char
	*egg_strndup(const char *s1, int a, int b)
{
	char	*copy;
	char	*res;
	int		i;

	i = 0;
	if (!ft_malloc(&copy, sizeof(char) * (b - a + 2)))
		safe_exit(1, "egg_strndup failed!");
	res = copy;
	while (a <= b)
		copy[i++] = s1[a++];
	copy[i] = '\0';
	return (res);
}
