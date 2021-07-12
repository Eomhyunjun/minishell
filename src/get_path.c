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
	char		*s;
	t_charbox	*current;

	current = all()->egg_envp;
	while (current)
	{
		s = current->data;
		if (s[0] == 'P' && s[1] == 'A'
			&& s[2] == 'T' && s[3] == 'H'
			&& s[4] == '=')
			return (ft_split(&s[5], ':'));
		current = current->next;
	}
	return (NULL);
}
