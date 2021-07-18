/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_request.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehokim <taehokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 13:20:06 by taehokim          #+#    #+#             */
/*   Updated: 2021/07/18 13:23:06 by taehokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

int
	request_update_env(char *name, char *value)
{
	int			mem_ret;
	t_charbox	*env;

	mem_ret = 0;
	env = find_envp(name);
	if (!value)
		mem_ret = send_env_code(ENV_NEW_NULL, name, NULL);
	else if (env && value)
		mem_ret = send_env_code(ENV_EDIT, name, value);
	else if (!env)
		mem_ret = send_env_code(ENV_NEW, name, value);
	return (mem_ret);
}
