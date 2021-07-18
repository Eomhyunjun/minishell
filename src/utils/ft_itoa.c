/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 13:25:56 by heom              #+#    #+#             */
/*   Updated: 2021/07/18 13:27:26 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

static int		signchk(int n)
{
	if (n < 0)
		return (-1);
	return (1);
}

static	int		len(int n)
{
	int		i;

	i = 0;
	if (n <= 0)
	{
		n = (-1) * n;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char			*ft_itoa(int n)
{
	char	*str;
	int		sign;
	int		i;

	if (n == -2147483648)
		return (egg_strdup("-2147483648"));
	i = len(n);
	sign = signchk(n);
	if (!(str = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	str[i--] = '\0';
	if (n == 0)
	{
		str[0] = '0';
		return (str);
	}
	n = sign * n;
	while (n > 0)
	{
		str[i--] = '0' + (n % 10);
		n = n / 10;
	}
	if (sign < 0)
		str[0] = '-';
	return (str);
}
