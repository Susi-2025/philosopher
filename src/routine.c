
#include "philo.h"
//lack of check simulation end in each phase

static int lock_fork(t_philo *philo);
static int think_phase(t_philo *philo);
static int eat_phase(t_philo *philo);
static int sleep_phase(t_philo *philo);

void *philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;

	while (!philo->table->start_time) // synchronous all philos
		;
	if (((philo->id - 1) % 2) != 0) // odd or even must wait
		usleep(1000);
	philo->last_meal_time = get_time(); // update the last_meal_time ?? is it correct
	while (philo->table->end_simu == 0) // if not end_simulation, allow to run
	{
		if (lock_fork(philo) == 1)
			break;
		if (eat_phase(philo) == 1)
			break ;
		if (sleep_phase(philo) == 1)
			break ;
		if (think_phase(philo) == 1)
			break ;
	}
	return (NULL);
}


static int think_phase(t_philo *philo)
{
	print_message(philo->table, philo->id, THINK);
	safe_usleep(philo->table, philo->table->think_time);
	if (philo->table->end_simu == 1)
		return (1);
	return (0);
}

static int lock_fork(t_philo *philo)
{
		pthread_mutex_lock(philo->left_fork);
		if (philo->table->end_simu == 1)
		{
			pthread_mutex_unlock(philo->left_fork);
			return (1);
		}
		print_message(philo->table, philo->id, FORK_PICK);
		pthread_mutex_lock(philo->right_fork);
		if (philo->table->end_simu == 1)
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			return (1);
		}
		return (0);
}

static int eat_phase(t_philo *philo)
{
	if (philo->table->end_simu == 1)
		return (1);
	philo->last_meal_time = get_time();
	print_message(philo->table, philo->id, EAT);
	safe_usleep(philo->table, philo->table->eat_time);
	if (philo->table->end_simu == 1)
		return (1);
	philo->have_eaten++;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (0);
}

static int sleep_phase(t_philo *philo)
{
	if (philo->table->end_simu == 1)
		return (1);
	print_message(philo->table, philo->id, SLEEP);
	safe_usleep(philo->table, philo->table->sleep_time);
	if (philo->table->end_simu == 1)
		return (1);
	return (0);
}

void safe_usleep(t_table *table, uint64_t duration)
{
	uint64_t start;

	start = get_time();
	while (!table->end_simu && (get_time() - start) < duration)
		usleep(500);
}