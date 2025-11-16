/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 19:18:25 by vinguyen          #+#    #+#             */
/*   Updated: 2025/11/16 10:37:26 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_simulation(t_table *table)
{
	int	i;

	i = 0;
	table->start_time = get_time();
	table->threads_create = 1;
	while (i < table->philo_num && table->end_simu == 0)
	{
		if (pthread_create(&table->threads[i], NULL, routine,
				&table->philos[i]) != 0)
		{
			table->end_simu = 1;
			table->err = 1;
			clean_thread(table, table->threads_create);
			break ;
		}
		table->threads_create++;
		i++;
	}
	monitoring(table);
	if (table->threads_create == table->philo_num)
		clean_thread(table, table->philo_num);
	return (SUCC);
}

void	monitoring(t_table *table)
{
	if (!table)
		return ;
	while (table->end_simu == 0)
	{
		if (check_die(table))
			table->end_simu = 1 ;
		if (check_full(table))
			table->end_simu = 1 ;
		usleep (500);
	}
}

int	check_die(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_num)
	{
		if ((get_time() - table->philos[i].last_meal_time) >= table->die_time)
		{
			print_message(table, table->philos[i].id, DIE);
			return (1);
		}
		i++;
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

void	one_running(t_table *table)
{
	table->start_time = get_time();
	table->philos[0].last_meal_time = get_time();
	pthread_mutex_lock(table->philos[0].left_fork);
	print_message(table, table->philos[0].id, FORK_PICK);
	pthread_mutex_unlock(table->philos[0].left_fork);
	while (table->end_simu == 0)
	{
		if (check_die(table))
			table->end_simu = 1 ;
		if (check_full(table))
			table->end_simu = 1 ;
		usleep (500);
	}
}
