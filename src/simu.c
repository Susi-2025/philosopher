/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:41:39 by vinguyen          #+#    #+#             */
/*   Updated: 2025/11/03 16:18:19 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_simulation(t_table *table)
{
	int	i;

	if (!table)
		return (FAIL);
	i = 0;
	while (i < table->philo_num)
	{
		if (pthread_create(&table->threads[i], NULL, philo_routine,
				&table->philos[i]) != 0)
			return (clean_data(table), FAIL);
		i++;
	}
	table->start_time = get_time();
	monitoring(table);
	i = 0;
	while (i < table->philo_num)
	{
		if (pthread_join(table->threads[i], NULL) != 0)
			return (clean_data(table), FAIL);
		i++;
	}
	return (SUCC);
}

void	monitoring(t_table *table)
{
	int	i;

	while (table->end_simu == 0)
	{
		i = 0;
		while (i < table->philo_num && table->end_simu == 0)
		{
			if (check_die(table, i))
				break ;
			i++;
		}
		if (check_full(table))
			table->end_simu = 1;
		usleep(500);
	}
}

void	one_running(t_table *table)
{
	int	i;

	table->start_time = get_time();
	table->philos->last_meal_time = get_time();
	pthread_mutex_lock(table->philos[0].left_fork);
	print_message(table, table->philos[0].id, FORK_PICK);
	pthread_mutex_unlock(table->philos[0].left_fork);
	while (table->end_simu == 0)
	{
		i = 0;
		while (i < table->philo_num)
		{
			if (check_die(table, i))
				break ;
			i++;
		}
		if (check_full(table))
			table->end_simu = 1;
		usleep(500);
	}
}

int	check_die(t_table *table, int i)
{
	uint64_t	wait_time;

	wait_time = get_time() - table->philos[i].last_meal_time;
	if (wait_time >= table->die_time)
	{
		table->end_simu = 1;
		print_message(table, table->philos[i].id, DIE);
		return (1);
	}
	return (0);
}

int	check_full(t_table *table)
{
	int	i;

	if (table->must_eat == 0)
		return (0);
	i = 0;
	while (i < table->philo_num)
	{
		if (table->philos[i].have_eaten < table->must_eat)
			return (0);
		i++;
	}
	return (1);
}
