/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosiphers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 18:44:27 by ahsalem           #+#    #+#             */
/*   Updated: 2022/09/09 08:31:20 by ahsalem          ###   ########.fr       */
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
# include <string.h>

typedef struct t_main_vars
{
	pthread_mutex_t	mutex;
	pthread_mutex_t	fork_mutex;
	pthread_mutex_t	state_mutex;
	int				n_phil;
	int				t_death;
	int				t_eat;
	int				t_sleep;
	int				n_meals;
	int				*sticks;
	int				*greedy;
	int				kill_every_body;
	long			start;
} t_main_vars;

typedef struct t_main_with_inc
{
	t_main_vars	*common;
	int			index_phil;
	char		state;
} t_main_with_inc;
//consider adding th survival to the struct above as int
typedef struct t_routine_vars
{
	int		current_phil;
	long	survival;
	long	update;
	int		my_fork;
	char	state;
} t_routine_vars;

t_main_vars	*parse_args(int argc, char **argv);
int			heart_attack(t_main_vars *t, t_routine_vars *r);
void		last_message(t_main_vars *t, t_routine_vars *r);
long		ft_atoi(const char *str);
int			ft_isdigit(int c);
int			check_args(char *str, int i);
int			*empty_stomach(int n_phil);
void		*routine(void *p);
void		think(t_main_vars *t, t_routine_vars *r);
void		nap(t_main_vars *t, t_routine_vars *r);
int			accomodation(t_main_vars *t,  t_routine_vars *r);
int			routine_logic(t_main_vars *t,struct timeval ct,t_routine_vars *r);
void		dining(int left_fork, int right_fork,t_main_vars *t,t_routine_vars *r);
void			lethal_spagetti(t_main_vars *t, t_routine_vars *r);
void		chewing(t_main_vars *t,  t_routine_vars *r);
void		feed_1st_philosipher(t_main_vars *t,  t_routine_vars *r);
void 		feed_last_philosipher(t_main_vars *t,  t_routine_vars *r);
void 		feed_other_philosiphers(t_main_vars *t,  t_routine_vars *r);
int			overthinking(t_main_vars *t,  t_routine_vars *r);
void		mem_clean(t_main_with_inc *arr_struc, t_main_vars *t, pthread_t *philosiphers);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
int			*buy_sticks(int sticks);
void		threading_operations(t_main_with_inc *arr_struc,
				int i, t_main_vars *t, pthread_t *philosiphers);
void		ft_usleep(int milli);
#endif
