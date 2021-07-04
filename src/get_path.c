/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 15:49:30 by heom              #+#    #+#             */
/*   Updated: 2021/07/04 16:49:23 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

char
	**get_path(void)
{
	int		i;
	char	*s;

	i = 0;
	while (all()->dup_envp[i])
	{
		s = all()->dup_envp[i];
		if (s[0] == 'P' && s[1] == 'A'
			&& s[2] == 'T' && s[3] == 'H'
			&& s[4] == '=')
			return (ft_split(&s[5], ':'));
		i++;
	}
	return (NULL);
}
