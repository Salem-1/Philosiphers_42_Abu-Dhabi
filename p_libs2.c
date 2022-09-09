/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_libs2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 09:26:29 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/09 07:17:25 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosiphers.h"

//check for the death hour while sleeping
void	ft_usleep(int milli)
{
	long	i;
	long	wait_till_I_finish;
	long	labs;
	struct timeval ct;
	long	elapsed_time;
	long	init_time;

	elapsed_time = 0;
	gettimeofday(&ct, NULL);
	init_time = ct.tv_sec * 1000000 + ct.tv_usec;
	labs = 60;
	i = 0;
	wait_till_I_finish = milli * 1000;
	while (elapsed_time / 1000 <= milli)
	{
		usleep(labs);
		gettimeofday(&ct, NULL);
		elapsed_time = ct.tv_sec * 1000000 + ct.tv_usec - init_time;
		i += labs;
	}
}

int	heart_attack(t_main_vars *t, t_routine_vars *r)
{
	struct timeval ct;

	gettimeofday(&ct, NULL);
	r->update = (ct.tv_sec * 1000000) + (ct.tv_usec );
	pthread_mutex_lock(&t->mutex);
	if (t->kill_every_body)
	{
		pthread_mutex_unlock(&t->mutex);
		return (1);
	}
	pthread_mutex_unlock(&t->mutex);
	if (((r->update - r->survival) / 1000) > t->t_death)
	{
		pthread_mutex_lock(&t->mutex);
		if (t->kill_every_body)
		{
			pthread_mutex_unlock(&t->mutex);
			return (1);
		}
		t->kill_every_body = 1;
		gettimeofday(&ct, NULL);
		r->update = (ct.tv_sec * 1000000) + (ct.tv_usec );
		printf("%ld Philosipher %d died heart_attack, value %ld, death %d\n",(r->update - t->start) / 1000, r->current_phil, ((r->update - r->survival) / 1000), t->t_death);
		pthread_mutex_unlock(&t->mutex);	
		return (1);
	}
	return (0);
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