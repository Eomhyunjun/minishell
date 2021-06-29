/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 20:02:09 by heom              #+#    #+#             */
/*   Updated: 2021/06/29 14:16:05 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

void
	safe_charbox_free(t_charbox *current)
{
	t_charbox	*removing;
	while (current)
	{
		removing = current;
		current = current->next;
		if (removing->data)
			free(removing->data);
		free(removing);
	}
}

void
	safe_cmd_free(void)
{
	t_cmd	*current;
	t_cmd	*removing;

	current = all()->cmd_info;
	while (current)
	{
		safe_charbox_free(current->io);
		safe_charbox_free(current->argv);
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
		printf("%s\n", msg);
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
