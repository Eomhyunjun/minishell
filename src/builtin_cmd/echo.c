/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 12:17:34 by taehokim          #+#    #+#             */
/*   Updated: 2021/07/23 16:34:19 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

int
	echo_print_free(t_charbox *print, int should_newline)
{
	char		*output;
	char		*tmp;

	output = to_chars(print, " ");
	free_charbox(print);
	if (should_newline == 1)
	{
		tmp = output;
		output = ft_strjoin3(output, "", "\n");
		free(tmp);
	}
	write(all()->builtin_stdout, output, ft_strlen(output));
	free(output);
	return (0);
}

int
	egg_echo(t_cmd *cmd)
{
	t_charbox	*arg;
	t_charbox	*print;
	int			should_newline;
	int			string_started;

	should_newline = 1;
	string_started = 0;
	print = NULL;
	arg = cmd->argv->next;
	while (arg)
	{
		if (ft_strlen(arg->data) == 2 && arg->data[0] == '-'
			&& arg->data[1] == 'n' && !string_started)
			should_newline = 0;
		else
		{
			string_started = 1;
			add_charbox(&print, egg_strdup(arg->data), 0);
		}
		arg = arg->next;
	}
	if (print == NULL)
		add_charbox(&print, create_blank(), 0);
	return (echo_print_free(print, should_newline));
}
