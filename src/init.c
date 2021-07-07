/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 15:21:31 by heom              #+#    #+#             */
/*   Updated: 2021/07/07 14:05:37 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

void	init(char **envp)
{
	all()->dup_envp = envp;
	all()->path = get_path();
	getcwd(all()->pwd, PATH_MAX);
}
