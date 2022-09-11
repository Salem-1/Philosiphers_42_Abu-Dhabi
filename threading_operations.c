/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading_operations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 18:44:24 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/11 16:59:21 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosiphers.h"

void	initiate_or_destroy_fork_mutexes_please(t_main_vars *t, char flag)
{
	int	i;
	
	i = 0;
	if (flag == 'i')
	{
		pthread_mutex_init(&t->meals_mutex, NULL);
		while (i < t->n_phil)
		{
			pthread_mutex_init(&t->fork_mutex[i], NULL);
			i++;
		}
	}
	else
	{
		pthread_mutex_destroy(&t->meals_mutex);
		while (i < t->n_phil)
		{
			pthread_mutex_destroy(&t->fork_mutex[i]);
			i++;
		}
		free(t->fork_mutex);
	}
}

void	mem_clean(t_main_with_inc *arr_struc, t_main_vars *t, pthread_t *philosiphers)
{
	pthread_mutex_destroy(&t->mutex);
	initiate_or_destroy_fork_mutexes_please(t, 'd');
	free(t->sticks);
	free(t->n_meals);
	free(t->greedy);
	free(t);
	free(philosiphers);
	free(arr_struc);
}

int	check_meals(t_main_vars *t)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&t->meals_mutex);
	if (t->n_meals[0] == -10)
	{
		pthread_mutex_unlock(&t->meals_mutex);
		return (0);
	}while (i < t->n_phil)
	{
		if (t->n_meals[i] == 0)
		{
			i++;
			continue;
		}
		else
		{
			pthread_mutex_unlock(&t->meals_mutex);
			return (0);
		}
		i++;
	}
	pthread_mutex_unlock(&t->meals_mutex);
	return (1);
}

void	threading_operations(t_main_with_inc *arr_struc,
		int i, t_main_vars *t, pthread_t *philosiphers)
{
	struct timeval	ct;

	gettimeofday(&ct, NULL);
	t->start = (ct.tv_sec * 1000000) + (ct.tv_usec );
	t->kill_every_body = 0;
	// printf(val"inside main i = %d, die == %d, eat = %d, sleep = %d,  n_meals = %d\n", i, t->t_death, t->t_eat,t->t_sleep,t->n_meals);
	while(i < t->n_phil )
	{
		arr_struc[i].common = t;
		arr_struc[i].index_phil = i + 1;
		arr_struc[i].state = 't';
		arr_struc[i].food_sched = !((i + 1) % 2 == 0);
		pthread_create(&philosiphers[i], NULL,
			 &routine, &arr_struc[i]);
		// usleep(400);
		i++;
	}
	i = 0;
	while(i <  t->n_phil )
	{
		pthread_join(philosiphers[i], NULL);
		i++;
	}
}

void	kill_in_main(t_main_vars *t)
{
	t->kill_every_body = 1;
}