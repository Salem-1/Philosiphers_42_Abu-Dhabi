/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daily_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 08:56:49 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/05 08:53:06 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosiphers.h"

//inshalla
//sync philosiphers habits
//Kill all philosiphers and close the program
//add eating flag for n_meals -= 1
//optimise/ check_leaks /Submit 

//create state to track the state of the philosipher 
/*if state thinking don't print, if state death (KILL EVERY BODY)*/
void	*routine(void *p)
{
	t_main_vars		*t;
	struct timeval	ct;
	t_routine_vars	r;

	t = (*(t_main_with_inc *)(p)).common;
	pthread_mutex_lock(&t->mutex);
	r.current_phil = (*(t_main_with_inc *)(p)).index_phil;
	pthread_mutex_unlock(&t->mutex);
	gettimeofday(&ct, NULL);
	if (routine_logic(t, ct, r) == 0)
		return (NULL);
	return (NULL);
}

int	routine_logic(t_main_vars *t,struct timeval ct,t_routine_vars r)
{
	pthread_mutex_lock(&t->mutex);
	printf("phils = %d, die == %d, eat = %d, sleep = %d,  n_meals = %d\n",r.current_phil, t->t_death, t->t_eat,t->t_sleep,t->n_meals);
	pthread_mutex_unlock(&t->mutex);
	pthread_mutex_lock(&t->mutex);
	r.survival = ct.tv_usec;
	pthread_mutex_unlock(&t->mutex);
	r.now = ct.tv_usec;
	
	while (t->t_death > ct.tv_usec - r.survival)
	{
		
		pthread_mutex_lock(&t->mutex);
		if (t->n_phil < 2)
		{
			pthread_mutex_unlock(&t->mutex);
			if (overthinking(t, ct, r) == 0)
				return (0);
		}
		else
			dining(t, ct, r);
		nap(t->t_sleep, r.current_phil, r.now, t);
		think(r.current_phil, r.now, t);
		gettimeofday(&ct, NULL);
	}
	pthread_mutex_lock(&t->mutex);
	printf("%ld Philosipher %d died\n", ct.tv_usec - r.now, r.current_phil);
	pthread_mutex_unlock(&t->mutex);
	return (1);
}

void	dining(t_main_vars *t,struct timeval ct,t_routine_vars r)
{
	t->n_phil -= 2;
	pthread_mutex_unlock(&t->mutex);
	gettimeofday(&ct, NULL);
	eat(t->t_eat, r.current_phil, r.now, t);
	pthread_mutex_lock(&t->mutex);
	t->n_phil += 2;
	pthread_mutex_unlock(&t->mutex);
	gettimeofday(&ct, NULL);
	r.survival = ct.tv_usec;
}

int	overthinking(t_main_vars *t,struct timeval ct,t_routine_vars r)
{
	while (1)
	{
		gettimeofday(&ct, NULL);
		pthread_mutex_lock(&t->mutex);
		if(t->t_death > ct.tv_usec - r.survival)
		{
			pthread_mutex_unlock(&t->mutex);
			pthread_mutex_lock(&t->mutex);
			printf("%ld Philosipher %d died\n", ct.tv_usec - r.now, r.current_phil);
			pthread_mutex_unlock(&t->mutex);
			return 0;
		}
		think(r.current_phil, r.now, t);
		pthread_mutex_lock(&t->mutex);
		if (t->n_phil > 1)
		{
			pthread_mutex_unlock(&t->mutex);
			return (1) ;
		}
	}
}