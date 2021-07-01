/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 18:43:48 by heom              #+#    #+#             */
/*   Updated: 2021/07/01 16:58:11 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"


char
	*to_chars_put_data(t_charbox *charbox, char *chars, char *div)
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
		i = 0;
		if (current->next)
			while (div[i])
				chars[j++] = div[i++];
		current = current->next;
	}
	return (chars);
}


char
	*to_chars(t_charbox *charbox, char *div)
{
	t_charbox	*current;
	long		i;
	long		total_len;
	char		*chars;
	long		div_len;

	div_len = ft_strlen(div);
	current = charbox;
	total_len = 0;
	while (current)
	{
		i = 0;
		while (current->data[i])
			i++;
		total_len += i;
		total_len += div_len;
		current = current->next;
	}
	total_len -= div_len;
	if (!(chars = malloc(sizeof(char) * (total_len + 1))))
		safe_exit(1, "to_chars chars malloc failed!");
	chars[total_len] = '\0';
	return (to_chars_put_data(charbox, chars, div));
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
