void feed_other_philosiphers(t_main_vars *t,  t_routine_vars *r)
{
	int	left;
	int	right;

	left = r->my_fork;
	if (r->current_phil == t->n_phil)
		right = 0;
	else
		right = left + 1;
	pthread_mutex_lock(&t->fork_mutex[left]);
	if (t->sticks[left] && (t->greedy[left] != r->current_phil))
	{
		pthread_mutex_unlock(&t->fork_mutex[left]);
		pthread_mutex_lock(&t->fork_mutex[right]);
		if (t->sticks[right] && (t->greedy[right] != r->current_phil))
		{
			pthread_mutex_unlock(&t->fork_mutex[right]);
			dining(left, right, t, r);
			pthread_mutex_lock(&t->fork_mutex[right]);
		}
		pthread_mutex_unlock(&t->fork_mutex[right]);
		
		pthread_mutex_lock(&t->fork_mutex[left]);
	}
		pthread_mutex_unlock(&t->fork_mutex[left]);
}



void	lock_forks(t_main_vars *t, int left, int right)
{
	pthread_mutex_lock(&t->fork_mutex[left]);
	pthread_mutex_lock(&t->fork_mutex[right]);
}

void	unlock_forks(t_main_vars *t, int left, int right)
{
	pthread_mutex_unlock(&t->fork_mutex[right]);
	pthread_mutex_unlock(&t->fork_mutex[left]);
}