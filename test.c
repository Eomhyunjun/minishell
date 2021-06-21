/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 15:54:30 by heom              #+#    #+#             */
/*   Updated: 2021/06/21 16:41:15 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/egginshell.h"

void test_add_cmds()
{
	add_cmds();
	add_cmds();
	add_cmds();
	add_cmds();
}

void test_add_cmd()
{
	add_cmds();
	add_cmd(&all()->cmds->cmd_info);
	add_cmd(&all()->cmds->cmd_info);
	add_cmd(&all()->cmds->cmd_info);
	add_cmd(&all()->cmds->cmd_info);
	t_cmd *a;
	for (a = all()->cmds->cmd_info; a; a = a->next)
	{
		printf("hi hos\n");
	}
}

int main(void)
{
	test_add_cmds();
	test_add_cmd();
	return (0);
}
