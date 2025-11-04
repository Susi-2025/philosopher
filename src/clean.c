/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:40:27 by vinguyen          #+#    #+#             */
/*   Updated: 2025/11/04 09:58:26 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	clean_pthread(pthread_mutex_t *forks, int len);

int	clean_data(t_table *table, int code)
{
	if (!table)
		return (-1);
	if (table->forks)
		clean_pthread(table->forks, table->philo_num);
	if (table->philos)
		free(table->philos);
	if (table->threads)
		free(table->threads);
	pthread_mutex_destroy(&table->print_lock);
	return (code);
}

static void	clean_pthread(pthread_mutex_t *forks, int len)
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
