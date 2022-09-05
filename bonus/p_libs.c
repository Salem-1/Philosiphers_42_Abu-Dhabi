/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_libs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 09:26:29 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/04 20:35:37 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosiphers.h"

int		ft_isspace(const char *c);
long	int_generator(const char *str, long num, int sign);

long	ft_atoi(const char *str)
{
	int		sign;
	long	num;

	num = 0;
	sign = 1;
	while (*str)
	{
		if (*str == '-' || *str == '+')
		{
			if (*str == '-')
				sign *= -1;
			str++;
			break ;
		}
		else if (*str >= '0' && *str <= '9')
			break ;
		else if (ft_isspace(str))
		{
			str++;
			continue ;
		}
		else
			return (0);
	}
	return (int_generator(str, num, sign));
}

int	ft_isspace(const char *c)
{
	if ((*c >= 9 && *c <= 13) || *c == 32)
		return (1);
	else
		return (0);
}

long	int_generator(const char *str, long num, int sign)
{
	int	outliar;

	outliar = 0;
	while (*str == '0')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + (*str - '0');
		str++;
		outliar++;
	}
	if (outliar > 18)
	{
		if (sign == -1)
			return (0);
		else
			return (-1);
	}
	return (num * sign);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
