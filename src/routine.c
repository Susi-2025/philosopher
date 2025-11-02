/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:41:29 by vinguyen          #+#    #+#             */
/*   Updated: 2025/11/02 17:55:46 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// lack of check simulation end in each phase

static int	lock_fork(t_philo *philo);
static int	think_phase(t_philo *philo);
static int	eat_phase(t_philo *philo);
static int	sleep_phase(t_philo *philo);
// static int	unlock_forks(t_philo *philo, int code);

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->table->start_time) // synchronous all philos
		;
	if (((philo->id - 1) % 2) != 0) // odd or even must wait
		usleep(1000);
	// philo->last_meal_time = get_time();
	while (philo->table->end_simu == 0) // if not end_simulation, allow to run
	{
		if (lock_fork(philo) == -1)
			break ;
		if (eat_phase(philo) == -1)
			break ;
		if (sleep_phase(philo) == -1)
			break ;
		if (think_phase(philo) == -1)
			break ;
	}
	return (NULL);
}

static int	think_phase(t_philo *philo)
{
	print_message(philo->table, philo->id, THINK);
	safe_usleep(philo->table, philo->table->think_time);
	if (philo->table->end_simu == 1)
		return (-1);
	return (0);
}

static int	lock_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (philo->table->end_simu == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		return (-1);
	}
	print_message(philo->table, philo->id, FORK_PICK);
	pthread_mutex_lock(philo->right_fork);
	philo->lock_status = 1;
	if (philo->table->end_simu == 1)
		return (unlock_forks(philo, -1));
	return (0);
}

static int	eat_phase(t_philo *philo)
{
	if (philo->table->end_simu == 1)
		return (unlock_forks(philo, -1));
	print_message(philo->table, philo->id, EAT);
	safe_usleep(philo->table, philo->table->eat_time);
	if (philo->table->end_simu == 1)
		return (unlock_forks(philo, -1));
	philo->last_meal_time = get_time();
	philo->have_eaten++;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	philo->lock_status = 0;
	// printf("[DEBUG] Philo %d: last_meal_time = %lu\n", philo->id, philo->last_meal_time);
	return (0);
}

static int	sleep_phase(t_philo *philo)
{
	if (philo->table->end_simu == 1 && philo->lock_status == 1)
		return (unlock_forks(philo, -1));
	print_message(philo->table, philo->id, SLEEP);
	safe_usleep(philo->table, philo->table->sleep_time);
	if (philo->table->end_simu == 1 && philo->lock_status == 1)
		return (unlock_forks(philo, -1));
	return (0);
}
