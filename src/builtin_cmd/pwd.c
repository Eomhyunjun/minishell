/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 14:19:21 by heom              #+#    #+#             */
/*   Updated: 2021/07/23 16:33:16 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

int
	egg_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	ft_putstr_plus_newline(all()->builtin_stdout, path);
	free(path);
	return (0);
}
