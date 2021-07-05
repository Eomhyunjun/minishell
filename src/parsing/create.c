/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 17:24:39 by heom              #+#    #+#             */
/*   Updated: 2021/07/05 17:26:06 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

char
	*create_blank(void)
{
	char	*blank;

	if (!ft_malloc(&blank, 1))
		safe_exit(1, "create blank failed");
	blank[0] = '\0';
	return (blank);
}

char
	*create_dollar(void)
{
	char	*dollar;

	if (!ft_malloc(&dollar, 2))
		safe_exit(1, "create dollar failed");
	dollar[0] = '$';
	dollar[1] = '\0';
	return (dollar);
}
