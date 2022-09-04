/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   habits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 08:56:49 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/04 07:30:22 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosiphers.h"

void	eat(int eating_time, int philo, int now)
{
	struct timeval			ct;

	gettimeofday(&ct, NULL);
	printf("%d Philoshpher %d is eating\n", ct.tv_usec - now, philo);
	usleep(eating_time);
	return ;
}

void	think(int philo, int now)
{
	struct timeval			ct;

	gettimeofday(&ct, NULL);
	printf("%d Philoshpher %d is thinking\n", ct.tv_usec - now, philo);
	return ;

}

void	nap(int nap_time, int philo, int now)
{
	struct timeval			ct;

	gettimeofday(&ct, NULL);
	printf("%d Philoshpher %d is sleeping\n", ct.tv_usec - now, philo);
	usleep(nap_time);
	return ;
}