/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 18:10:31 by heom              #+#    #+#             */
/*   Updated: 2021/07/05 17:09:12 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

char
	*ft_strjoin(char const *s1, char const *mid, char const *s2)
{
	char	*bottle;
	int		i;

	i = 0;
	if ((s1 == 0) || (s2 == 0) || (mid == 0))
		return (0);
	ft_malloc(&bottle, (ft_strlen(s1) + ft_strlen(s2) + ft_strlen(mid) + 1));
	while (*s1)
		bottle[i++] = *s1++;
	while (*mid)
		bottle[i++] = *mid++;
	while (*s2)
		bottle[i++] = *s2++;
	bottle[i] = '\0';
	return (bottle);
}
