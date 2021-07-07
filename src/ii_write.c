/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ii_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 15:43:28 by heom              #+#    #+#             */
/*   Updated: 2021/07/07 15:57:54 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

void	ii_write(void)
{
	t_cmd		*current;
	t_charbox	*input;
	char		*data;

	current = all()->cmd_info;
	while (current)
	{
		input = current->last_input;
		if (input && input->type == RD_II)
		{
			data = ft_strjoin3(input->data, "\n", "");
			write(current->ii_fd[1], data, ft_strlen(data));
			free(data);
		}
		current = current->next;
	}
}
