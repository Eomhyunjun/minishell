/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_charbox.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 18:43:48 by heom              #+#    #+#             */
/*   Updated: 2021/06/28 18:43:56 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

void	add_charbox(t_charbox **container, char *allocated, int type)
{
	t_charbox *new_box;
	t_charbox *last_box;

	if ((new_box = malloc(sizeof(t_charbox))) == 0)
		safe_exit(1, "new_box malloc failed!");
	ft_bzero(new_box, sizeof(t_charbox));
	new_box->data = allocated;
	new_box->type = type;
	if (*container == NULL)
	{
		*container = new_box;
		return ;
	}
	last_box = *container;
	while (last_box->next)
		last_box = last_box->next;
	last_box->next = new_box;
}
