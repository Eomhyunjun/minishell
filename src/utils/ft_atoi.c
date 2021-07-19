/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 14:01:28 by heom              #+#    #+#             */
/*   Updated: 2021/07/19 20:40:27 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int
	is_num(char num)
{
	if (num < '0' || num > '9')
		return (0);
	return (1);
}

static int
	ft_isspace(char c)
{
	if (c == '\f' || c == '\n' || c == '\r'
		|| c == '\t' || c == '\v' || c == ' ')
		return (1);
	return (0);
}

int
	ft_atoi(const char *str)
{
	long long	result;
	long long	sign;
	long long	post_result;

	(void)post_result;
	result = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		++str;
	}
	while (*str)
	{
		if (is_num(*str))
		{
			result = result * 10 + ((*str++) - '0');
		}
		else
			break ;
	}
	return (sign * result);
}
