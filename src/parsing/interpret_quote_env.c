/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_quote_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 19:30:34 by heom              #+#    #+#             */
/*   Updated: 2021/07/05 16:09:57 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

void
	interpret_quote_env_loop(t_oil *o)
{
	char	*chars;

	is_quote(o->data[o->i], &o->quote);
	if (o->data[o->i] == '$' || o->data[o->i] == '"' || o->data[o->i] == '\'')
	{
		if ((o->quote == Q_SINGLE && o->data[o->i] == '$')
			|| (o->quote == Q_DOUBLE && o->data[o->i] == '\'')
			|| (o->quote == Q_SINGLE && o->data[o->i] == '"'))
			;
		else
		{
			if (o->start <= o->i - 1)
			{
				chars = egg_strndup(o->data, o->start, o->i - 1);
				add_charbox(&o->box, chars, 0);
			}
			if (o->data[o->i] == '$')
			{
				o->i = make_dollar(o->data, o->i + 1, &chars);
				add_charbox(&o->box, chars, 0);
			}
			o->start = o->i + 1;
		}
	}
}

char
	*interpret_quote_env(char *data)
{
	t_oil	o;
	char	*chars;
	char	*res;

	o.i = 0;
	o.start = 0;
	o.quote = Q_NONE;
	o.box = NULL;
	o.data = data;
	while (o.data[o.i])
	{
		interpret_quote_env_loop(&o);
		o.i++;
	}
	chars = egg_strndup(o.data, o.start, o.i - 1);
	add_charbox(&o.box, chars, 0);
	// " 열린 채로 끝났을 때 에러 처리 필요함.
	res = to_chars(o.box, "");
	free_charbox(o.box);
	return (res);
}

void
	interpret_charbox(t_charbox *charbox)
{
	char		*tmp;
	t_charbox	*current;

	current = charbox;
	while (current)
	{
		tmp = current->data;
		current->data = interpret_quote_env(current->data);
		free(tmp);
		current = current->next;
	}
}
