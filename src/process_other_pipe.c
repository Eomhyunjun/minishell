/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_other_pipe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehokim <taehokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 13:44:13 by heom              #+#    #+#             */
/*   Updated: 2021/07/19 15:29:31 by taehokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

char
	*create_chars_from_fd(int fd, int *total_len)
{
	char	buf[1024];
	char	*raw_str;
	char	*tmp;
	int		read_len;
	int		i;

	if (!ft_malloc(&raw_str, 1))
		return (NULL);
	raw_str[0] = '\0';
	*total_len = 0;
	while (1)
	{
		read_len = read(fd, buf, 1023);
		if (read_len == 0 || read_len == -1)
			break;
		i = 0;
		tmp = raw_str;
		if (!ft_malloc(&raw_str, *total_len + read_len))
		{
			free(tmp);
			return (NULL);
		}
		i = -1;
		while (++i < *total_len)
			raw_str[i] = tmp[i];
		i = -1;
		while (++i < read_len)
			raw_str[i + *total_len] = buf[i];
		*total_len += read_len;
		free(tmp);
	}
	return (raw_str);
}

int
	process_cd(char *raw_str, int i)
{
	char	*path;
	int		success;
	char	*msg;

	i += 2;
	path = egg_strdup(&raw_str[i]);
	if (chdir(path))
	{
		success = 0;
		msg = ft_strjoin4("egginshell: cd: ", path, ": ", strerror(errno));
		ft_putstr_plus_newline(2, msg);
		free(msg);
	}
	free(path);
	if (success)
	{
		path = getcwd(NULL, 0);
		if (edit_envp("PWD", path))
			safe_exit(1, "pwd memory error while cd");
		free(path);
	}
	return (i + ft_strlen(&raw_str[i]));
}

void
	process_other_pipe(void)
{
	char	*raw_str;
	int		i;
	int		len;

	raw_str = create_chars_from_fd(all()->other_pipe[0], &len);
	i = 0;
	while (i < len)
	{
		if (raw_str[i] == OTHER_CD)
			i = process_cd(raw_str, i);
		i++;
	}
}
