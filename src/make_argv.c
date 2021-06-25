/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 15:22:35 by heom              #+#    #+#             */
/*   Updated: 2021/06/25 17:14:55 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

void	add_iobox(t_iobox **container, char *allocated, int io_type)
{
	t_iobox *new_box;
	t_iobox *last_box;

	if ((new_box = malloc(sizeof(t_iobox))) == 0)
		safe_exit(1, "new_box malloc failed!");
	ft_bzero(new_box, sizeof(t_iobox));
	new_box->data = allocated;
	new_box->type = io_type;
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

int		add_io(t_cmd *current, int io_type, int i)
{
	int		start;
	int		end;
	char	*dub_res;
	char	*rawcmd;

	i++;
	rawcmd = current->rawcmd;
	i = get_none_space_pos(rawcmd, i);
	start = i;
	i = get_none_name_pos(rawcmd, i);
	end = i - 1;
	dub_res = egg_strndup(rawcmd, start, end);
	if (dub_res[0] == '\0')
		token_error(rawcmd[i]);
	add_iobox(&current->io, dub_res, io_type);
	return (i);
}

int		io_try_push(t_cmd *current, int i)
{
	char	*rawcmd;

	rawcmd = current->rawcmd;
	i = get_none_space_pos(current->rawcmd, i);
	if (!rawcmd[i])
		return (i);
	if (rawcmd[i] == '<' && rawcmd[i + 1] != '<')
		i = add_io(current, RD_I, i);
	else if (rawcmd[i] == '<' && rawcmd[i + 1] == '<')
		i = add_io(current, RD_II, i + 1);
	else if (rawcmd[i] == '>' && rawcmd[i + 1] != '>')
		i = add_io(current, RD_O, i);
	else if (rawcmd[i] == '>' && rawcmd[i + 1] == '>')
		i = add_io(current, RD_OO, i + 1);
	return (i);
}

void	make_argv_item(t_cmd *current)
{
	int		quote;
	int		i;

	i = 0;
	quote = Q_NONE;
	while (current->rawcmd[i])
	{
		if (!is_quote(current->rawcmd[i], &quote))
		{
			i = io_try_push(current, i); // only io exit error
			// i = cmd_try_push(current, i);
		}
		i++;
	}
}

void	make_argv(void)
{
	t_cmd	*current;

	current = all()->cmd_info;
	while (current)
	{
		make_argv_item(current);
		current = current->next;
	}
}
