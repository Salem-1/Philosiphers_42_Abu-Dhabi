/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 18:44:24 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/10 11:05:53 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosiphers.h"

int main(int argc, char **argv)
{
	t_main_vars		*t;
	pthread_t		*philosiphers;
	int				i;
	t_main_with_inc *arr_struc;

	i = 0;
	philosiphers = NULL;
	if (!(argc == 5 || argc == 6))
		return (0);
	t = parse_args(argc, argv);
	if (!t)
		return (0);
	philosiphers = ft_calloc(sizeof(pthread_t) , t->n_phil );
	if (!philosiphers)
	{
		free(t);
		return (0);
	}
	pthread_mutex_init(&t->mutex, NULL);
	initiate_or_destroy_fork_mutexes_please(t, 'i');
	arr_struc  = ft_calloc(sizeof(t_main_with_inc) ,t->n_phil );
	if (arr_struc)
		threading_operations(arr_struc, i, t,philosiphers);
	mem_clean(arr_struc, t, philosiphers);
	return (0);
}

void	initiate_or_destroy_fork_mutexes_please(t_main_vars *t, char flag)
{
	int	i;
	
	i = 0;
	if (flag == 'i')
	{
		while (i < t->n_phil)
		{
			pthread_mutex_init(&t->fork_mutex[i], NULL);
			i++;
		}
	}
	else
	{
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
	free(t->greedy);
	free(t);
	free(philosiphers);
	free(arr_struc);
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
		pthread_create(&philosiphers[i], NULL,
			 &routine, &arr_struc[i]);
		// usleep(10);
		i++;
	}
	i = 0;
	while(i <  t->n_phil )
	{
		pthread_join(philosiphers[i], NULL);
		i++;
	}
}
