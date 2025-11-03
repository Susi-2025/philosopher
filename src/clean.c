/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:40:27 by vinguyen          #+#    #+#             */
/*   Updated: 2025/11/02 15:40:30 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	void	clean_pthread(pthread_mutex_t *forks, int len);

void	clean_data(t_table *table)
{
	if (!table)
		return ;
	if (table->forks)
		clean_pthread(table->forks, table->philo_num);
	if (table->philos)
		free(table->philos);
	if (table->threads)
		free(table->threads);
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->end);
}

static	void	clean_pthread(pthread_mutex_t *forks, int len)
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
	clean_data(table);
	return (code);
}

int	unlock_forks(t_philo *philo, int code)
{
	if (philo->lock_status == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		philo->lock_status = 0;
	}
	return (code);
}
