/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catering.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:21:46 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/09 07:17:35 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosiphers.h"

void	lethal_spagetti(t_main_vars *t, t_routine_vars *r)
{
	if (r->current_phil == 1)
	{
		feed_1st_philosipher(t, r);
	}
	else if (r->current_phil == t->n_phil)
	{
		feed_last_philosipher(t, r);
	}
	else
	{
		feed_other_philosiphers(t, r);
	}
}

void	dining(int left_fork, int right_fork, t_main_vars *t, t_routine_vars *r)
{
	struct timeval ct;

	pthread_mutex_lock(&t->fork_mutex);
	t->sticks[left_fork] = 0;
	t->sticks[right_fork] = 0;
	t->greedy[left_fork] = r->current_phil;
	t->greedy[right_fork] = r->current_phil;
	pthread_mutex_unlock(&t->fork_mutex);
	if(heart_attack(t, r))
		return ;
	pthread_mutex_lock(&t->mutex);
	gettimeofday(&ct, NULL);
	r->update = (ct.tv_sec * 1000000) + (ct.tv_usec );
	printf("%ld Philosipher %d has taken a fork\n",(r->update - t->start) / 1000, r->current_phil);
	printf("%ld Philosipher %d has taken a fork\n",(r->update - t->start) / 1000, r->current_phil);
	printf("%ld Philoshpher %d is eating\n",(r->update - t->start) / 1000, r->current_phil);
	gettimeofday(&ct, NULL);
	r->survival = (ct.tv_sec * 1000000) + (ct.tv_usec );
	pthread_mutex_unlock(&t->mutex);
	ft_usleep(t->t_eat);
	pthread_mutex_lock(&t->fork_mutex);
	t->sticks[left_fork] = 1;
	t->sticks[right_fork] = 1;
	pthread_mutex_unlock(&t->fork_mutex);
	r->state= 'e';
}

void feed_1st_philosipher(t_main_vars *t,  t_routine_vars *r)
{
	pthread_mutex_lock(&t->fork_mutex);
	if (t->sticks[r->my_fork] && t->sticks[r->my_fork + 1]
			&&((t->greedy[r->my_fork] != r->current_phil) &&
				(t->greedy[r->my_fork + 1] != r->current_phil)
				))
	{
		pthread_mutex_unlock(&t->fork_mutex);
		dining(r->my_fork, r->my_fork + 1, t, r);
		pthread_mutex_lock(&t->fork_mutex);
	}
	pthread_mutex_unlock(&t->fork_mutex);
}


void feed_last_philosipher(t_main_vars *t,  t_routine_vars *r)
{
	pthread_mutex_lock(&t->fork_mutex);
	if ((t->sticks[r->my_fork] && t->sticks[1])
			&&((t->greedy[r->my_fork] != r->current_phil) &&
				(t->greedy[1] != r->current_phil)
					))
	{
		pthread_mutex_unlock(&t->fork_mutex);
		dining(r->my_fork, 1, t, r);
		pthread_mutex_lock(&t->fork_mutex);
	}
	pthread_mutex_unlock(&t->fork_mutex);
}

void feed_other_philosiphers(t_main_vars *t,  t_routine_vars *r)
{
	pthread_mutex_lock(&t->fork_mutex);
	if ((t->sticks[r->my_fork] && t->sticks[r->my_fork + 1])
		&&((t->greedy[r->my_fork] != r->current_phil) &&
				(t->greedy[r->my_fork + 1] != r->current_phil)
					))
	{
		pthread_mutex_unlock(&t->fork_mutex);
		dining(r->my_fork, r->my_fork + 1, t, r);
		pthread_mutex_lock(&t->fork_mutex);
	}
	pthread_mutex_unlock(&t->fork_mutex);
}









