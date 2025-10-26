
#include "philo.h"
//need to check the start time of philo
// skip the odd philo to prevent racing
// update last time time
// show message thinking
// pick fork;

static	void	pick_fork(t_philo *philo);

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	
	while (!philo->table->start_time) // synchronous all philos
		;
	if (((philo->id - 1) % 2) != 0) // odd or even must wait
		usleep (1000);
	philo->last_meal_time = get_time(); // update the last_meal_time ?? is it correct
	while(philo->table->end_simu == 0) // if not end_simulation, allow to run
	{
		think_phase(philo);
		pick_fork(philo);
		eat_phase(philo);
		sleep_phase(philo);
	}
	return (NULL);
}

static	void	think_phase(t_philo *philo)
{
	uint64_t	current_time;

	current_time = get_time();
	while (current_time < philo->table->think_time)
		print_message(philo->table, philo->id, THINK);
}

static	void	pick_fork(t_philo *philo)// not for only 1 philo
{
	print_message(philo->table, philo->id, FORK_PICK);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
}

static	void	eat_phase(t_philo *philo)
{
	uint64_t	current_time;

	current_time = get_time();
	while (current_time < philo->table->eat_time)
		print_message(philo->table, philo->id, EAT);
}

static	void	sleep_phase(t_philo *philo)
{
	uint64_t	current_time;

	current_time = get_time();
	while (current_time < philo->table->sleep_time)
		print_message(philo->table, philo->id, SLEEP);
}