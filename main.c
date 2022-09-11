/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 18:44:24 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/11 17:03:16 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosiphers.h"

int	main(int argc, char **argv)
{
	t_main_with_inc	*arr_struc;
	t_main_vars		*t;
	pthread_t		*philosiphers;
	int				i;

	i = 0;
	philosiphers = NULL;
	if (!(argc == 5 || argc == 6))
		return (0);
	t = parse_args(argc, argv);
	if (!t)
		return (0);
	philosiphers = ft_calloc(sizeof(pthread_t), t->n_phil);
	if (!philosiphers)
	{
		free(t);
		return (0);
	}
	pthread_mutex_init(&t->mutex, NULL);
	initiate_or_destroy_fork_mutexes_please(t, 'i');
	arr_struc = ft_calloc(sizeof(t_main_with_inc), t->n_phil);
	if (arr_struc)
		threading_operations(arr_struc, i, t, philosiphers);
	mem_clean(arr_struc, t, philosiphers);
	return (0);
}
