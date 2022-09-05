/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   habits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 08:56:49 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/05 08:53:37 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosiphers.h"

void	eat(int eating_time, int philo, int now, t_main_vars *t)
{
	struct timeval			ct;

	gettimeofday(&ct, NULL);
	pthread_mutex_lock(&t->mutex);
	printf("%ld Philoshpher %d is eating\n", ct.tv_usec - now, philo);
	pthread_mutex_unlock(&t->mutex);
	usleep(eating_time);
	return ;
}

void	think(int philo, int now, t_main_vars *t)
{
	struct timeval			ct;

	gettimeofday(&ct, NULL);
	pthread_mutex_lock(&t->mutex);
	printf("%ld Philoshpher %d is thinking\n", ct.tv_usec - now, philo);
	pthread_mutex_unlock(&t->mutex);
	return ;

}

void	nap(int nap_time, int philo, int now, t_main_vars *t)
{
	struct timeval			ct;

	gettimeofday(&ct, NULL);
	pthread_mutex_lock(&t->mutex);
	printf("%ld Philoshpher %d is sleeping\n", ct.tv_usec - now, philo);
	pthread_mutex_unlock(&t->mutex);
	usleep(nap_time);
	return ;
}