/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 15:41:29 by heom              #+#    #+#             */
/*   Updated: 2021/07/04 16:29:20 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void
	ft_bzero(void *s, size_t n)
{
	unsigned char	*c;

	c = s;
	while (n--)
		*c++ = 0;
}
