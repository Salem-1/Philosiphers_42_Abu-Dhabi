/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 09:17:24 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/04 11:36:17 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosiphers.h"

t_main_vars	*parse_args(int argc, char **argv)
{
	t_main_vars	*t;
	int			i;

	i = 1;
	while (argv[i])
	{
		if (!(check_args(argv[i], i)))
		{
			printf("Error in parsing");
			return (NULL);
		}
		i++;
	}
	t = malloc(sizeof(t_main_vars) * 1);
	if (!t)
		return (NULL);
	// t->n_phil = malloc(sizeof(int));
	// if(!t->n_phil)
	// 	return (NULL);
	t->n_phil = ft_atoi(argv[1]);
	t->t_death = ft_atoi(argv[2]);
	t->t_eat = ft_atoi(argv[3]);
	t->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		t->n_meals = ft_atoi(argv[5]);
	else
		t->n_meals = -1;
	return (t);
}


int	check_args(char *str, int i)
{
	i = 0;
	if (!*str)
		return (0);
	while (str[i])
	{
		if (!(ft_isdigit(str[i])))
		{
			if (str[i + 1])
			{
				if (!(str[i] == '+')
						&& ft_isdigit(str[i + 1]))
					return (0);
			}
			else
				return (0);
		}
		else if ((str[i + 1] && ft_isdigit(str[i])
				&& (str[i + 1] == '+')))
			return (0);
		i++;
	}
	if ((ft_atoi(str) > 2147483647)
		|| ft_atoi(str) < (-2147483647 - 1))
		return (0);
	if (ft_atoi(str) < 0)
		{
			printf("Sorry Cannot go back in time\n");
			return (0);
		}
	return (1);
}
