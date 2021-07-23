/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 18:53:19 by heom              #+#    #+#             */
/*   Updated: 2021/07/23 15:24:03 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

void
	unset_envp(char *name)
{
	t_charbox	*arg;

	arg = find_envp(name);
	if (!arg)
		return ;
	if (arg->prev)
		arg->prev->next = arg->next;
	if (arg->next)
		arg->next->prev = arg->prev;
	free(arg->data);
	free(arg);
}

void
	print_unset_error(char *data)
{
	char	*msg;

	msg = ft_strjoin3("egginshell: unset: '",
			data, "': not a valid identifier");
	ft_putstr_plus_newline(2, msg);
	free(msg);
}

int
	validate_unset(char *data, char **name)
{
	int	i;

	if (!can_be_first_env_name(data[0]))
	{
		print_unset_error(data);
		return (1);
	}
	i = 1;
	while (data[i])
	{
		if (!can_be_env_name(data[i]))
		{
			print_unset_error(data);
			return (1);
		}
		i++;
	}
	*name = egg_strndup(data, 0, i - 1);
	return (0);
}

void
	unset_path(void)
{
	free_char_double_ptr(all()->path);
	all()->path = ft_split("", ' ');
}

int
	egg_unset(t_cmd *cmd)
{
	t_charbox	*arg;
	int			ret;
	char		*name;

	ret = 0;
	if (charbox_len(cmd->argv) > 1)
	{
		arg = cmd->argv->next;
		while (arg)
		{
			if (validate_unset(arg->data, &name))
				ret = 1;
			else
			{
				unset_envp(name);
				if (ft_strcmp(name, "PATH") == 0)
					unset_path();
			}
			if (name)
				free(name);
			arg = arg->next;
		}
	}
	return (ret);
}
