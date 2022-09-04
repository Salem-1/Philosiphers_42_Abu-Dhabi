/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 18:44:24 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/04 09:48:47 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosiphers.h"

int main(int argc, char **argv)
{
	// t_main_with_inc	pass_to_th;
	t_main_vars		*t;
	pthread_t		*philosiphers;
	int				i;
	t_main_with_inc *arr_struc;

	i = 1;
	if (!(argc == 5 || argc == 6))
		return (0);
	t = parse_args(argc, argv);
	if (!t)
		return (0);
	philosiphers = malloc(sizeof(pthread_t) * t->n_phil);
	if (!philosiphers)
	{
		free(t);
		return (0);
	}
	pthread_mutex_init(&t->mutex, NULL);
	arr_struc  = malloc(sizeof(t_main_with_inc) * t->n_phil);
	while(i < t->n_phil + 1)
	{
		arr_struc[i].common = t;
		arr_struc[i].index_phil = i;
			pthread_create(&philosiphers[i], NULL, &routine, &arr_struc[i]);
		i++;
		
	}
	i = 1;
	while(i <  t->n_phil + 1)
	{
		pthread_join(philosiphers[i], NULL);
		return (0);
			i++;
	}
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

// void	threading_operations(t_main_with_inc *arr_struc,
// 		int i, t_main_vars *t, pthread_t *philosiphers)
// {
	
// }