/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 14:19:09 by heom              #+#    #+#             */
/*   Updated: 2021/06/21 15:57:47 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"


void	init(char **envp)
{
	all()->dup_envp = envp;
}


void	parse(char *buf)
{
	int i;

	i =0;
	add_cmds();
	while (buf[i])
	{
		if (buf[i] == '\"')
		{

		}
		else if (buf[i] == '\'')
		{

		}
		else
		{

		}
	}
}

int		main(int argc, char **argv, char **envp)
{
	char *buf = "cat abc.txt > a > b > c | cat b; cat c";

	init(envp);
	parse(buf);





	//add_rds(all()->cmds[0], "a");
	//add_rds(all()->cmds[0], "b");
	//add_rds(all()->cmds[0], "c");

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
