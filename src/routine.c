/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 19:18:00 by vinguyen          #+#    #+#             */
/*   Updated: 2025/11/03 19:19:12 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	lock_forks(t_philo *philo);
static int	eat_sleep_think(t_philo *philo);

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->id % 2 == 0)
		usleep(2000);
	philo->last_meal_time = get_time();
	print_message(philo->table, philo->id, THINK);
	while (philo->table->end_simu == 0)
	{
		if (lock_forks(philo) == -1)
			break ;
		if (eat_sleep_think(philo) == -1)
			break ;
	}
	return (NULL);
}

static int	lock_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (philo->table->end_simu)
	{
		pthread_mutex_unlock(philo->left_fork);
		return (-1);
	}
	print_message(philo->table, philo->id, FORK_PICK);
	pthread_mutex_lock(philo->right_fork);
	if (philo->table->end_simu)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (-1);
	}
	print_message(philo->table, philo->id, FORK_PICK);
	return (0);
}

static int	eat_sleep_think(t_philo *philo)
{
	print_message(philo->table, philo->id, EAT);
	philo->last_meal_time = get_time();
	philo->have_eaten++;
	safe_usleep(philo->table, philo->table->eat_time);
	if (philo->table->end_simu)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (-1);
	}
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	print_message(philo->table, philo->id, SLEEP);
	safe_usleep(philo->table, philo->table->sleep_time);
	if (philo->table->end_simu)
		return (-1);
	print_message(philo->table, philo->id, THINK);
	safe_usleep(philo->table, philo->table->think_time);
	if (philo->table->end_simu)
		return (-1);
	return (0);
}
