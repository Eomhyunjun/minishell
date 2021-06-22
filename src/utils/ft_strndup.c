/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 19:23:17 by heom              #+#    #+#             */
/*   Updated: 2021/06/22 19:23:51 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../egginshell.h"

char	*ft_strndup(const char *s1, int a, int b)
{
	char	*copy;
	char	*res;
	int		i;

	i = 0;
	if (!(copy = (char *)malloc(sizeof(char) * (b - a + 2))))
		return (NULL);
	res = copy;
	while (a <= b)
		copy[i++] = s1[a++];
	copy[i] = '\0';
	return (res);
}
