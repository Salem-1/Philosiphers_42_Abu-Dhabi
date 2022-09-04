/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosiphers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 18:44:27 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/04 09:42:20 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSIPHERS_H
# define PHILOSIPHERS_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

typedef struct t_main_vars
{
	int		n_phil;
	int		t_death;
	int		t_eat;
	int		t_sleep;
	int		n_meals;
	pthread_mutex_t	mutex;
} t_main_vars;

typedef struct t_main_with_inc
{
	t_main_vars *common;
	int	index_phil;
} t_main_with_inc;

typedef struct t_routine_vars
{
	int	current_phil;
	int	survival;
	int	now;
} t_routine_vars;

t_main_vars	*parse_args(int argc, char **argv);
void	threading_operations(t_main_with_inc *arr_struc,
		int i, t_main_vars *t, pthread_t *philosiphers);
long		ft_atoi(const char *str);
int			ft_isdigit(int c);
int			check_args(char *str, int i);
void		*routine(void *p);
void		eat(int eating_time, int philo, int now);
void		think(int philo, int now);
void		nap(int nap_time, int philo, int now);
int			routine_logic(t_main_vars *t,struct timeval ct,t_routine_vars r);
void		dining(t_main_vars *t,struct timeval ct,t_routine_vars r);
int		overthinking(t_main_vars *t,struct timeval ct,t_routine_vars r);
void	mem_clean(t_main_with_inc *arr_struc, t_main_vars *t, pthread_t *philosiphers);

void		*forks(void *p);
#endif
