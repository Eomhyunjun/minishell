/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 18:43:48 by heom              #+#    #+#             */
/*   Updated: 2021/06/29 15:24:11 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"


char
	*to_chars_put_data(t_charbox *charbox, char *chars)
{
	t_charbox	*current;
	long		i;
	long		j;

	current = charbox;
	j = 0;
	while (current)
	{
		i = 0;
		while (current->data[i])
			chars[j++] = current->data[i++];
		current = current->next;
	}
	return (chars);
}


char
	*to_chars(t_charbox *charbox)
{
	t_charbox	*current;
	long		i;
	long		j;
	char		*chars;

	current = charbox;
	j = 0;
	while (current)
	{
		i = 0;
		while (current->data[i])
			i++;
		j += i;
		current = current->next;
	}
	if (!(chars = malloc(sizeof(char) * (j + 1))))
		safe_exit(1, "to_chars chars malloc failed!");
	chars[j] = '\0';
	return (to_chars_put_data(charbox, chars));
}

//할당해서 box에 data랑 type 넣어주는 함수
void
	add_charbox(t_charbox **container, char *allocated, int type)
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
