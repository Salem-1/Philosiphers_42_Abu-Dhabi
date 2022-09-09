/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daily_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 08:56:49 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/09 09:03:34 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//this is the test for greedy philosophers problem
//make && ./philosophers 3 410 200 100

#include "philosiphers.h"
//kill everybody
//do the shared var meals flag
//Create ft_usleep to check the death of the philospher in each iteration

//stuck in infinite loop, check by print

void	*routine(void *p)
{
	t_main_vars		*t;
	struct timeval	ct;
	t_routine_vars	r;


	t = (*(t_main_with_inc *)(p)).common;
	pthread_mutex_lock(&t->mutex);
	r.state = (*(t_main_with_inc *)(p)).state;
	r.current_phil = (*(t_main_with_inc *)(p)).index_phil;
	r.my_fork = r.current_phil - 1;
	pthread_mutex_unlock(&t->mutex);
	gettimeofday(&ct, NULL);
	r.state= 'a';
	if (routine_logic(t, ct, &r) == 0)
		return (NULL);
	return (NULL);
}


int	routine_logic(t_main_vars *t,struct timeval ct, t_routine_vars *r)
{
	gettimeofday(&ct, NULL);
	r->survival = (ct.tv_sec * 1000000) + (ct.tv_usec );
	r->update = (ct.tv_sec * 1000000) + (ct.tv_usec );
	while (1)
	{
		if(heart_attack(t, r))
			return (0);
		if (r->state == 't' || r->state == 'a')
			lethal_spagetti(t, r);
		if(heart_attack(t, r))
			return (0);
		if (r->state == 'e' && accomodation(t, r) == 0)
				return (0);
		if(heart_attack(t, r))
			return (0);
		if (r->state == 's' || r->state == 't' )
		{
			if (overthinking(t, r) == 0)
				return (0);
		}
	}
	return (1);
}

int	overthinking(t_main_vars *t, t_routine_vars *r)
{
	if (r->state != 't')
	{
		if(heart_attack(t, r))
			return (0);
		pthread_mutex_lock(&t->mutex);
		if (t->kill_every_body)
		{
			pthread_mutex_unlock(&t->mutex);	
			return (0);
		}
		if (r->state != 't')
			printf("%ld Philosopher %d is thinking\n",(r->update - t->start) / 1000, r->current_phil);
		pthread_mutex_unlock(&t->mutex);
		r->state = 't';
	}
	if(heart_attack(t, r))
			return (0);
	return (1);
}

int	accomodation(t_main_vars *t,  t_routine_vars *r)
{
	if(heart_attack(t, r))
		return (0);
	pthread_mutex_lock(&t->mutex);
	if (t->kill_every_body)
	{
		pthread_mutex_unlock(&t->mutex);	
		return (0);
	}
	printf("%ld Philosopher %d is sleeping\n",(r->update - t->start) / 1000, r->current_phil);
	pthread_mutex_unlock(&t->mutex);
	ft_usleep(t->t_sleep);
	r->state = 's';
	if(heart_attack(t, r))
		return (0);
	return (1);
}
