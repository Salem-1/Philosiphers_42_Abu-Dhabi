/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daily_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 08:56:49 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/04 08:58:01 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosiphers.h"

//inshalla
//print the args upon entry
//sync philosiphers habits
//Kill all philosiphers and close the program
//add eating flag for n_meals -= 1
//optimise/ check_leaks /Submit 


void	*routine(void *p)
{
	t_main_vars		*t;
	struct timeval	ct;
	t_routine_vars	r;

	t = (*(t_main_with_inc *)(p)).common;
	r.current_phil = (*(t_main_with_inc *)(p)).index_phil;
	gettimeofday(&ct, NULL);
	if (routine_logic(t, ct, r) == 0)
		return (NULL);
	return (NULL);
}

int	routine_logic(t_main_vars *t,struct timeval ct,t_routine_vars r)
{
	printf("phils = %d, die == %d, eat = %d, sleep = %d,  n_meals = %d\n",r.current_phil, t->t_death, t->t_eat,t->t_sleep,t->n_meals);
	r.survival = ct.tv_usec;
	r.now = ct.tv_usec;
	while (t->t_death > ct.tv_usec - r.survival)
	{
		pthread_mutex_lock(&t->mutex);
		if (t->n_phil < 2)
		{
			if (overthinking(t, ct, r) == 0)
				return (0);
		}
		else
			dining(t, ct, r);
		pthread_mutex_unlock(&t->mutex);
		nap(t->t_sleep, r.current_phil, r.now);
		if (overthinking(t, ct, r) == 0)
			return (0);
		gettimeofday(&ct, NULL);
	}
	return (1);
}

void	dining(t_main_vars *t,struct timeval ct,t_routine_vars r)
{
	t->n_phil -= 2;
	pthread_mutex_unlock(&t->mutex);
	gettimeofday(&ct, NULL);
	eat(t->t_eat, r.current_phil, r.now);
	pthread_mutex_lock(&t->mutex);
	t->n_phil += 2;
	gettimeofday(&ct, NULL);
	r.survival = ct.tv_usec;
}

int	overthinking(t_main_vars *t,struct timeval ct,t_routine_vars r)
{
	while (1)
	{
		gettimeofday(&ct, NULL);
		if(t->t_death > ct.tv_usec - r.survival)
		{
			printf("%d Philosipher %d died\n", ct.tv_usec - r.now, r.current_phil);
			return 0;
		}
		think(r.current_phil, r.now);
		if (t->n_phil > 1)
			return (1) ;
		gettimeofday(&ct, NULL);
	}
}