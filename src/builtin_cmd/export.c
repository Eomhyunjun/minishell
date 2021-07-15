/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 10:49:52 by taehokim          #+#    #+#             */
/*   Updated: 2021/07/15 20:16:01 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

void
	print_export_error(char *data)
{
	char	*msg;

	msg = ft_strjoin3("egginshell: export: '", data, "': not a valid identifier");
	ft_putstr_plus_newline(2, msg);
	free(msg);
}

int
	validate_export(char *data, char **name, char **value)
{
	int	i;
	int	len;

	len = ft_strlen(data);
	if (!can_be_first_env_name(data[0]))
	{
		print_export_error(data);
		return (1);
	}
	i = 1;
	while (data[i] && data[i] != '=')
	{
		if (!can_be_env_name(data[i]))
		{
			print_export_error(data);
			return (1);
		}
		i++;
	}
	*name = egg_strndup(data, 0, i - 1);
	if (data[i] == '\0')
		*value = NULL;
	else
		*value = egg_strndup(data, i + 1, len - 1);
	return (0);
}

void
	export_display(void)
{
	t_charbox	*current;
	char		*print;
	char		*name;
	char		*value;
	char		*tmp;

	current = all()->egg_envp;
	print_charbox("envp", all()->egg_envp);
	while (current)
	{
		validate_export(current->data, &name, &value);
		print = ft_strjoin3("declare -x ", "", name);
		if (value)
		{
			tmp = print;
			print = ft_strjoin4(print, "=\"", value, "\"");
			free(tmp);
			free(value);
		}
		ft_putstr_plus_newline(1, print);
		free(print);
		free(name);
		current = current->next;
	}
}

int
	egg_export(t_cmd *cmd)
{
	t_charbox	*arg;
	t_charbox	*env;
	int			ret;
	int			mem_ret;
	char		*name;
	char		*value;

	ret = 0;
	mem_ret = 0;
	if (charbox_len(cmd->argv) > 1)
	{
		arg = cmd->argv->next;
		while (arg)
		{
			if (validate_export(arg->data, &name, &value))
				ret = 1;
			else
			{
				env = find_envp(name);
				if (!value)
					mem_ret = send_env_code(ENV_NEW_NULL, name, NULL);
				else if (env && value)
					mem_ret = send_env_code(ENV_EDIT, name, value);
				else if (!env)
					mem_ret = send_env_code(ENV_NEW, name, value);
			}
			if (name)
				free(name);
			if (value)
				free(value);
			if (mem_ret == 1)
				safe_exit(2, "export memory error");
			arg = arg->next;
		}
	}
	else
		export_display();
	return (ret);
}
