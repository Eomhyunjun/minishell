/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 20:02:09 by heom              #+#    #+#             */
/*   Updated: 2021/07/04 13:51:55 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "egginshell.h"

void
	free_charbox(t_charbox *charbox)
{
	t_charbox	*removing;

	while (charbox)
	{
		removing = charbox;
		charbox = charbox->next;
		if (removing->data)
			free(removing->data);
		free(removing);
	}
}

void
	free_char_double_ptr(char **pp)
{
	int	i;

	i = 0;
	while (pp[i])
	{
		free(pp[i]);
		i++;
	}
	free(pp);
}

void
	safe_cmd_free(void)
{
	t_cmd	*current;
	t_cmd	*removing;

	current = all()->cmd_info;
	while (current)
	{
		free_charbox(current->io);
		free_charbox(current->argv);
		free_charbox(current->theredoc);
		removing = current;
		current = current->next;
		if (removing->rawcmd)
			free(removing->rawcmd);
		free(removing);
	}
	all()->cmd_info = 0;
}

void
	safe_exit(int code, char *msg)
{
	safe_cmd_free();
	if (code != 0 && msg && msg[0])
		ft_putstr(2, msg);
	exit(code);
}

void
	token_error(char token)
{
	safe_cmd_free();
	if (token == '\n')
		printf("syntax error near unexpected token 'newline'\n");
	else
		printf("syntax error near unexpected token '%c'\n", token);
	exit(1);
}
