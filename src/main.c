/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 14:19:09 by heom              #+#    #+#             */
/*   Updated: 2021/06/22 20:14:56 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"


void	init(char **envp)
{
	all()->dup_envp = envp;
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
		if (buf[i] == '\"' && quote != Q_SINGLE)
			if (quote == Q_DOUBLE)
				quote = Q_NONE;
			else
				quote = Q_DOUBLE;
		else if (buf[i] == '\'' && quote != Q_DOUBLE)
			if (quote == Q_SINGLE)
				quote = Q_NONE;
			else
				quote = Q_SINGLE;
		else if (buf[i] == '|' && quote == Q_NONE)
		{
			add_cmd(ft_strndup(buf, cmd_start, i - 1)); // have to free
			cmd_start = i + 1;
		}
		i++;
	}
	add_cmd(ft_strndup(buf, cmd_start, i - 1)); // have to free
	// should check if quote is open
	// should check if only one pipe char end
}


void	parse(char *buf)
{
	make_rawcmd(buf);

}

int		main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	char *buf = "cat abc.txt > a > b > \'c  \"| \'cat b | cat c | helloworld |";

	init(envp);
	parse(buf);
	t_cmd *cmd;
	cmd = all()->cmd;
	while (cmd)
	{
		printf("%s\n", cmd->rawcmd);
		cmd = cmd->next;
	}


	//add_rds(all()->cmds[0], "a");
	//add_rds(all()->cmds[0], "b");
	//add_rds(all()->cmds[0], "c");
	safe_exit(0, NULL);
	return (0);
}




/*
void	add_rds(t_cmd *cmd, char *rd)
{
	int		len;
	char	**new_rds;
	int		i;

	if (cmd->rds == NULL)
	{
		cmd->rds = malloc(sizeof(char *));
		cmd->rds[0] = NULL;
	}
	len = pptr_len(cmd->rds);
	new_rds = malloc(sizeof(char *) * (len + 2));
	new_rds[len] = NULL;
	i = 0;
	while (i < len)
	{
		new_rds[i] = cmd->rds[i];
		i++;
	}
	free(cmd->rds);
	cmd->rds = new_rds;
}

int	pptr_len(char **chars)
{
	int	i;

	i = 0;
	while (chars[i])
	{
		i++;
	}
	return (i);
}
*/
