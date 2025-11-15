/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 19:18:00 by vinguyen          #+#    #+#             */
/*   Updated: 2025/11/15 14:57:41 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	lock_forks(t_philo *philo);
static int	eat_sleep_think(t_philo *philo);
static int	lock_first_fork(t_philo *philo, pthread_mutex_t *first_fork);
static int	lock_second_fork(t_philo *philo, pthread_mutex_t *first_fork,
				pthread_mutex_t *second_fork);

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

static int	eat_sleep_think(t_philo *philo)
{
	philo->last_meal_time = get_time();
	print_message(philo->table, philo->id, EAT);
	safe_usleep(philo->table, philo->table->eat_time);
	if (philo->table->end_simu)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (-1);
	}
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo->have_eaten++;
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

static int	lock_first_fork(t_philo *philo, pthread_mutex_t *first_fork)
{
	pthread_mutex_lock(first_fork);
	if (philo->table->end_simu)
	{
		pthread_mutex_unlock(first_fork);
		return (-1);
	}
	print_message(philo->table, philo->id, FORK_PICK);
	return (0);
}

static int	lock_second_fork(t_philo *philo, pthread_mutex_t *first_fork,
							pthread_mutex_t *second_fork)
{
	pthread_mutex_lock(second_fork);
	if (philo->table->end_simu)
	{
		pthread_mutex_unlock(first_fork);
		pthread_mutex_unlock(second_fork);
		return (-1);
	}
	print_message(philo->table, philo->id, FORK_PICK);
	return (0);
}

static int	lock_forks(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->id % 2 == 0)
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	else
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	if (lock_first_fork(philo, first_fork) == -1)
		return (-1);
	if (lock_second_fork(philo, first_fork, second_fork) == -1)
		return (-1);
	return (0);
}
