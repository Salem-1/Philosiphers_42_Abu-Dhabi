/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 18:44:24 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/04 20:36:24 by ahsalem          ###   ########.fr       */
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
		//I have an invalidwrite here causing valgrind issues
		//wrong sizeof in 31 and 40 
	philosiphers = ft_calloc(sizeof(pthread_t) , t->n_phil );
	if (!philosiphers)
	{
		free(t);
		return (0);
	}
	// memset((void *)(philosiphers), 0, sizeof(pthread_t) * t->n_phil);
	pthread_mutex_init(&t->mutex, NULL);
	//printf(" n_phils =%d, main_with_inc = %ld \n",t->n_phil, sizeof(t_main_with_inc));
	//create cal
	arr_struc  = ft_calloc(sizeof(t_main_with_inc) ,t->n_phil );
	if (arr_struc)
		threading_operations(arr_struc, i, t,philosiphers);
	mem_clean(arr_struc, t, philosiphers);
	return (0);
}

void	mem_clean(t_main_with_inc *arr_struc, t_main_vars *t, pthread_t *philosiphers)
{
	pthread_mutex_destroy(&t->mutex);
	free(t);
	free(philosiphers);
	free(arr_struc);
}

void	threading_operations(t_main_with_inc *arr_struc,
		int i, t_main_vars *t, pthread_t *philosiphers)
{
	i = 0;
	while(i < t->n_phil )
	{
		arr_struc[i].common = t;
		// printf("inside main i = %d, die == %d, eat = %d, sleep = %d,  n_meals = %d\n", i, t->t_death, t->t_eat,t->t_sleep,t->n_meals);
		arr_struc[i].index_phil = i + 1;
		pthread_create(&philosiphers[i], NULL,
			 &routine, &arr_struc[i]);
		i++;
	}
	i = 0;
	while(i <  t->n_phil )
	{
		pthread_join(philosiphers[i], NULL);
		i++;
	}
}