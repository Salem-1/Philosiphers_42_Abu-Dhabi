/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catering.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:21:46 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/11 15:49:20 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosiphers.h"

void	lethal_spagetti(t_main_vars *t, t_routine_vars *r)
{
	if (t->n_phil == 1)
		return ;
	feed_other_philosiphers(t, r);
}

void	dining(int left_fork, int right_fork, t_main_vars *t, t_routine_vars *r)
{
	pthread_mutex_lock(&t->fork_mutex[left_fork]);
	t->sticks[left_fork] = 0;
	t->greedy[left_fork] = r->current_phil;
	pthread_mutex_unlock(&t->fork_mutex[left_fork]);
	pthread_mutex_lock(&t->fork_mutex[right_fork]);
	t->sticks[right_fork] = 0;
	t->greedy[right_fork] = r->current_phil;
	pthread_mutex_unlock(&t->fork_mutex[right_fork]);
	if(heart_attack(t, r))
		return ;
	pthread_mutex_lock(&t->mutex);
	chewing(t, r);
	pthread_mutex_lock(&t->meals_mutex);
	if (t->n_meals[r->current_phil - 1] > 0)
		t->n_meals[r->current_phil - 1] -= 1;
	pthread_mutex_unlock(&t->meals_mutex);
	pthread_mutex_unlock(&t->mutex);
	ft_usleep(t->t_eat, t, r);
	pthread_mutex_lock(&t->fork_mutex[left_fork]);
	t->sticks[left_fork] = 1;
	pthread_mutex_unlock(&t->fork_mutex[left_fork]);
	pthread_mutex_lock(&t->fork_mutex[right_fork]);
	t->sticks[right_fork] = 1;
	pthread_mutex_unlock(&t->fork_mutex[right_fork]);
	if(heart_attack(t, r))
		return ;
	r->state= 'e';
}

void	chewing(t_main_vars *t,  t_routine_vars *r)
{
	struct timeval ct;
	if (t->kill_every_body)
		return ;
	gettimeofday(&ct, NULL);
	r->update = (ct.tv_sec * 1000000) + (ct.tv_usec );
	printf("%ld %d has taken a fork\n",(r->update - t->start) / 1000, r->current_phil);
	printf("%ld %d has taken a fork\n",(r->update - t->start) / 1000, r->current_phil);
	printf("%ld %d is eating\n",(r->update - t->start) / 1000, r->current_phil);
	gettimeofday(&ct, NULL);
	r->survival = (ct.tv_sec * 1000000) + (ct.tv_usec );
}

void feed_other_philosiphers(t_main_vars *t,  t_routine_vars *r)
{
	int	left;
	int	right;

	left = r->my_fork;
	if (r->current_phil == t->n_phil)
		right = 0;
	else
		right = left + 1;
	pthread_mutex_lock(&t->fork_mutex[left]);
	if (t->sticks[left] && (t->greedy[left] != r->current_phil))
	{
		pthread_mutex_unlock(&t->fork_mutex[left]);
		pthread_mutex_lock(&t->fork_mutex[right]);
		if (t->sticks[right] && (t->greedy[right] != r->current_phil))
		{
			pthread_mutex_unlock(&t->fork_mutex[right]);
			dining(left, right, t, r);
			pthread_mutex_lock(&t->fork_mutex[right]);
		}
		pthread_mutex_unlock(&t->fork_mutex[right]);
		
		pthread_mutex_lock(&t->fork_mutex[left]);
	}
		pthread_mutex_unlock(&t->fork_mutex[left]);
}
