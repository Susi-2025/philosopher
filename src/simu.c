/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:41:39 by vinguyen          #+#    #+#             */
/*   Updated: 2025/11/02 17:55:31 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_simulation(t_table *table)
{
	unsigned int	i;

	if (!table)
		return (FAIL);
	i = 0;
	table->start_time = get_time();
	while (i < table->philo_num)
	{
		if (pthread_create(&table->threads[i], NULL, philo_routine,
				&table->philos[i]) != 0)
			return (clean_data(table), FAIL);
		i++;
	}
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
	unsigned int	i;
	uint64_t		wait_time;
	unsigned int	full_count;

	while (table->end_simu == 0)
	{
		i = 0;
		full_count = 0;
		while (i < table->philo_num)
		{
			wait_time = get_time() - table->philos[i].last_meal_time;
			// printf("[MONITOR] Philo %d: wait_time = %lu (last_meal = %lu)\n",
			// 	table->philos[i].id, wait_time, table->philos[i].last_meal_time);
			if (wait_time >= table->die_time)
			{
				print_message(table, table->philos[i].id, DIE);
				table->end_simu = 1;
				return ;
			}
			if (table->must_eat != 0
				&& table->philos[i].have_eaten == table->must_eat)
				full_count++;
			i++;
		}
		if (table->must_eat != 0 && full_count == table->philo_num)
		{
			table->end_simu = 1;
			return ;
		}
		safe_usleep(table, 200);
	}
}

void	safe_usleep(t_table *table, uint64_t duration)
{
	uint64_t	start;

	start = get_time();
	while (!table->end_simu && (get_time() - start) < duration)
		usleep(500);
}
