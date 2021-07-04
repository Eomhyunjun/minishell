/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 18:43:48 by heom              #+#    #+#             */
/*   Updated: 2021/07/04 16:49:59 by heom             ###   ########.fr       */
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
	if (!ft_malloc(&chars, sizeof(char) * (total_len + 1)))
		safe_exit(1, "to_chars chars malloc failed!");
	chars[total_len] = '\0';
	return (to_chars_put_data(charbox, chars, div));
}

int
	charbox_len(t_charbox *charbox)
{
	int			i;
	t_charbox	*current;

	current = charbox;
	i = 0;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}

char
	**to_double_ptr(t_charbox *charbox)
{
	t_charbox	*current;
	int			len;
	int			i;
	char		**ret;
	char		*pushing;

	len = charbox_len(charbox);
	if (!ft_malloc(&ret, sizeof(char *) * (len + 1)))
		safe_exit(1, "to_double_ptr malloc failed");
	ret[len] = 0;
	current = charbox;
	i = 0;
	while (current)
	{
		pushing = egg_strdup(current->data);
		ret[i] = pushing;
		i++;
		current = current->next;
	}
	return (ret);
}

void
	add_charbox(t_charbox **container, char *allocated, int type)
{
	t_charbox	*new_box;
	t_charbox	*last_box;

	if (!ft_malloc(&new_box, sizeof(t_charbox)))
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
