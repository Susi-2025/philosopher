/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:41:29 by vinguyen          #+#    #+#             */
/*   Updated: 2025/11/03 16:16:22 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	lock_fork(t_philo *philo);
static int	est_phase(t_philo *philo);

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->table->start_time)
		;
	if (((philo->id - 1) % 2) != 0)
		usleep(3000);
	philo->last_meal_time = get_time();
	print_message(philo->table, philo->id, THINK);
	while (philo->table->end_simu == 0)
	{
		if (lock_fork(philo) == -1)
			break ;
		if (est_phase(philo) == -1)
			break ;
	}
	return (NULL);
}

static int	lock_fork(t_philo *philo)
{
	if (philo->table->end_simu == 1)
		return (-1);
	pthread_mutex_lock(philo->left_fork);
	if (philo->table->end_simu == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		return (-1);
	}
	print_message(philo->table, philo->id, FORK_PICK);
	pthread_mutex_lock(philo->right_fork);
	if (philo->table->end_simu == 1)
		return (unlock_forks(philo, -1));
	print_message(philo->table, philo->id, FORK_PICK);
	return (0);
}

static int	est_phase(t_philo *philo)
{
	print_message(philo->table, philo->id, EAT);
	philo->last_meal_time = get_time();
	philo->have_eaten++;
	safe_usleep(philo->table, philo->table->eat_time);
	if (philo->table->end_simu == 1)
		return (unlock_forks(philo, -1));
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (philo->table->end_simu == 1)
		return (-1);
	print_message(philo->table, philo->id, SLEEP);
	safe_usleep(philo->table, philo->table->sleep_time);
	if (philo->table->end_simu == 1)
		return (-1);
	print_message(philo->table, philo->id, THINK);
	safe_usleep(philo->table, philo->table->think_time);
	if (philo->table->end_simu == 1)
		return (-1);
	return (0);
}
