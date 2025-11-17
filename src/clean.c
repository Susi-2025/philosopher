/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:40:27 by vinguyen          #+#    #+#             */
/*   Updated: 2025/11/17 15:56:50 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	clean_forks(pthread_mutex_t *forks, int len);

int	clean_data(t_table *table, int code)
{
	if (!table)
		return (-1);
	if (table->philos)
	{
		free(table->philos);
		table->philos = NULL;
	}
	if (table->threads)
	{
		free(table->threads);
		table->threads = NULL;
	}
	if (table->print_initial == 1)
	{
		pthread_mutex_destroy(&table->print_lock);
		if (table->forks && table->forks_initial == 1)
			clean_forks(table->forks, table->philo_num);
		else if (table->forks && table->forks_initial == 0)
		{
			free(table->forks);
			table->forks = NULL;
		}
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
	forks = NULL;
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
	if (num > table->philo_num)
		num = table->philo_num;
	while (i < num)
	{
		if (pthread_join(table->threads[i], NULL) != 0)
		{
			pthread_detach(table->threads[i]);
			write(2, "ERROR: pthread_join\n", 21);
		}
		i++;
	}
}

int	err_malloc(t_table *table, int code)
{
	if (!table)
		return (-1);
	printf("Malloc error or print_initial error\n");
	if (table->forks)
	{
		free(table->forks);
		table->forks = NULL;
	}
	if (table->philos)
	{
		free(table->philos);
		table->philos = NULL;
	}
	if (table->threads)
	{
		free(table->threads);
		table->threads = NULL;
	}
	return (code);
}
