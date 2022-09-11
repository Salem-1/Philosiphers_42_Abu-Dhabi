/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_libs2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 09:26:29 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/11 17:12:24 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosiphers.h"

//check for the death hour while sleeping
void	ft_usleep(int milli, t_main_vars *t, t_routine_vars *r)
{
	struct timeval	ct;
	long			labs;
	long			elapsed_time;
	long			init_time;

	elapsed_time = 0;
	gettimeofday(&ct, NULL);
	init_time = ct.tv_sec * 1000000 + ct.tv_usec;
	labs = 60;
	while (elapsed_time / 1000 <= milli - 1)
	{
		usleep(labs);
		gettimeofday(&ct, NULL);
		elapsed_time = ct.tv_sec * 1000000 + ct.tv_usec - init_time;
		if (heart_attack(t, r))
			return ;
	}
}

int	heart_attack(t_main_vars *t, t_routine_vars *r)
{
	struct timeval	ct;

	gettimeofday(&ct, NULL);
	r->update = (ct.tv_sec * 1000000) + (ct.tv_usec);
	pthread_mutex_lock(&t->mutex);
	if (t->kill_every_body)
	{
		pthread_mutex_unlock(&t->mutex);
		return (1);
	}
	pthread_mutex_unlock(&t->mutex);
	if ((((r->update - r->survival) / 1000) >= t->t_death)
		|| check_meals(t))
	{
		pthread_mutex_lock(&t->mutex);
		if (t->kill_every_body || check_meals(t))
		{
			pthread_mutex_unlock(&t->mutex);
			return (1);
		}
		last_message(t, r);
		pthread_mutex_unlock(&t->mutex);
		return (1);
	}
	return (0);
}

void	last_message(t_main_vars *t, t_routine_vars *r)
{
	struct timeval	ct;

	kill_in_main(t);
	gettimeofday(&ct, NULL);
	r->update = (ct.tv_sec * 1000000) + (ct.tv_usec);
	printf("%ld %d died\n", (r->update - t->start) / 1000, r->current_phil);
}

void	*ft_calloc(size_t count, size_t size)
{
	int		*result;

	result = malloc(size * count);
	if (!result)
		return (NULL);
	ft_bzero(result, count * size);
	return ((void *)result);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*((unsigned char *) s + i) = 0;
		i++;
	}
}
