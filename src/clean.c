/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:40:27 by vinguyen          #+#    #+#             */
/*   Updated: 2025/11/16 10:40:20 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	clean_forks(pthread_mutex_t *forks, int len);

int	clean_data(t_table *table, int code)
{
	if (!table)
		return (-1);
	if (table->philos)
		free(table->philos);
	if (table->threads)
		free(table->threads);
	if (table->print_initial == 1)
	{
		pthread_mutex_destroy(&table->print_lock);
		if (table->forks && table->forks_initial == 1)
			clean_forks(table->forks, table->philo_num);
	}
	return (code);
}

static void	clean_forks(pthread_mutex_t *forks, int len)
{
	int	i;

	if (!forks)
		return ;
	i = 0;
	while (i < len)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
}

int	err_clean(t_table *table, int code)
{
	if (!table)
		return (code);
	clean_data(table, 0);
	return (code);
}

void	clean_thread(t_table *table, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_join(table->threads[i], NULL);
		i++;
	}
}
