/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 21:01:16 by heom              #+#    #+#             */
/*   Updated: 2021/06/28 21:01:26 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

int		is_quote(char c, int *quote)
{
	if (c == '\"' && *quote != Q_SINGLE)
		if (*quote == Q_DOUBLE)
			*quote = Q_NONE;
		else
			*quote = Q_DOUBLE;
	else if (c == '\'' && *quote != Q_DOUBLE)
	{
		if (*quote == Q_SINGLE)
			*quote = Q_NONE;
		else
			*quote = Q_SINGLE;
	}
	if (*quote == Q_NONE)
		return (0);
	return (1);
}
