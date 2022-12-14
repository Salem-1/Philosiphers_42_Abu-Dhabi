/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 09:17:24 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/11 17:08:47 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosiphers.h"

t_main_vars	*parse_args(int argc, char **argv)
{
	t_main_vars	*t;
	int			i;

	i = 0;
	while (argv[++i])
	{
		if (!(check_args(argv[i], i)))
			return (NULL);
	}
	t = malloc(sizeof(t_main_vars) * 1);
	if (!t)
		return (NULL);
	t->kill_every_body = 0;
	t->n_phil = ft_atoi(argv[1]);
	t->t_death = ft_atoi(argv[2]);
	t->t_eat = ft_atoi(argv[3]);
	t->t_sleep = ft_atoi(argv[4]);
	t->sticks = buy_sticks(t->n_phil);
	t->greedy = empty_stomach(t->n_phil);
	t->fork_mutex = give_me_my_fork_please(t);
	if (argc == 6)
		t->n_meals = give_me_meal_boxes_please(ft_atoi(argv[5]), t);
	else
		t->n_meals = give_me_meal_boxes_please(-10, t);
	return (t);
}

int	*give_me_meal_boxes_please(int meals, t_main_vars	*t)
{
	int	*happy_meal;
	int	i;

	i = 0;
	happy_meal = ft_calloc(sizeof(int), t->n_phil);
	if (!happy_meal)
		return (NULL);
	while (i < t->n_phil)
	{
		happy_meal[i] = meals;
		i++;
	}
	return (happy_meal);
}

pthread_mutex_t	*give_me_my_fork_please(t_main_vars	*t)
{
	pthread_mutex_t	*fork_locks;

	fork_locks = ft_calloc(sizeof(pthread_mutex_t), t->n_phil);
	if (!fork_locks)
		return (NULL);
	return (fork_locks);
}

int	*empty_stomach(int n_phil)
{
	int	*ledger;
	int	i;

	i = 0;
	ledger = ft_calloc(sizeof(int), n_phil);
	if (!ledger)
		return (NULL);
	while (i < n_phil)
	{
		ledger[i] = -1;
		i++;
	}
	return (ledger);
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
				if (!(str[i] == '+') && ft_isdigit(str[i + 1]))
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
	if ((ft_atoi(str) > 2147483647) || ft_atoi(str) < (-2147483648))
		return (0);
	if (ft_atoi(str) < 0)
		return (0);
	return (1);
}
