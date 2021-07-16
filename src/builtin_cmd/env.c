/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 15:27:43 by heom              #+#    #+#             */
/*   Updated: 2021/07/16 15:32:10 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

int
	egg_env(void)
{
	t_charbox	*current;

	current = all()->egg_envp;
	while (current)
	{
		ft_putstr_plus_newline(1, current->data);
		current = current->next;
	}
	return (0);
}
