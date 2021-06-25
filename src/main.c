/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 14:19:09 by heom              #+#    #+#             */
/*   Updated: 2021/06/25 17:14:23 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

int		is_quote(char c, int *quote)
{
	if (c == '\"' && *quote != Q_SINGLE)
		if (*quote == Q_DOUBLE)
			*quote = Q_NONE;
		else
			*quote = Q_DOUBLE;
	else if (c == '\'' && *quote != Q_DOUBLE)
	{
		if (*quote == Q_SINGLE)
			*quote = Q_NONE;
		else
			*quote = Q_SINGLE;
	}
	if (*quote == Q_NONE)
		return (0);
	return (1);
}

void	make_rawcmd(char *buf)
{
	int	i;
	int cmd_start;
	int	quote;

	i = 0;
	quote = Q_NONE;
	cmd_start = 0;
	while (buf[i])
	{
		if (!is_quote(buf[i], &quote) && buf[i] == '|')
		{
			add_cmd(egg_strndup(buf, cmd_start, i - 1));
			cmd_start = i + 1;
		}
		i++;
	}
	add_cmd(egg_strndup(buf, cmd_start, i - 1));
	// should check if quote is open
	// should check if only one pipe end
}


void	parse(char *buf)
{
	make_rawcmd(buf);
	make_argv();
}

int		main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	char *buf = "< 1abc       <<    bbb           <  asdfds | <sdf";

	init(envp);
	parse(buf);
	t_cmd *cmd;
	cmd = all()->cmd_info;
	while (cmd)
	{
		printf("pipe : %s\n", cmd->rawcmd);
		t_iobox *current;
		current = cmd->io;
		while (current)
		{
			printf("type : %d, s : |%s|\n", current->type, current->data);
			current = current->next;
		}
		cmd = cmd->next;
	}

	safe_exit(0, NULL);
	return (0);
}


