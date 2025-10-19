
#include "philo.h"
//need to check the start time of philo
// skip the odd philo to prevent racing
// update last time time
// show message thinking
// pick fork;

static	int	pick_fork(t_philo *philo);

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	
	while (!philo->table->start_time)
		;
	if (((philo->id - 1) % 2) != 0)
		usleep (1000);
	philo->last_meal_time = get_time();
	if (print_message(philo->table, philo->id, THINK) == FAIL)
		return (NULL);
	while(philo->table->end_simu == 0)
	{
		if (pick_fork(philo) == FAIL)
			break ;
	}
	return (NULL);
}

static	int	pick_fork(t_philo *philo)
{
	if (print_message(philo->table, philo->id, FORK_PICK) == FAIL)
		return (FAIL);
	if (pthread_mutex_lock(philo->left_fork) == FAIL)
		return (FAIL);
	if (pthread_mutex_lock(philo->right_fork) == FAIL)
	{
		pthread_mutex_unlock(philo->left_fork);
		return (FAIL);
	}
	return (SUCC);
}