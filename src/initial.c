/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:40:56 by vinguyen          #+#    #+#             */
/*   Updated: 2025/11/16 10:48:07 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	parsing_table(t_table *table, char *av[], int ac);
static int	init_mem_table(t_table *table);
static int	init_mutex_table(t_table *table);

int	init_table(t_table *table, char *av[], int ac)
{
	parsing_table(table, av, ac);
	if (init_mem_table(table) == FAIL)
		return (FAIL);
	if (init_mutex_table(table) == FAIL)
		return (FAIL);
	return (SUCC);
}

int	init_philo(t_table *table)
{
	int	i;

	if (!table || !table->philos || !table->forks)
		return (FAIL);
	i = 0;
	while (i < table->philo_num)
	{
		table->philos[i].id = i + 1;
		table->philos[i].table = table;
		table->philos[i].left_fork = &table->forks[i];
		if (i == (table->philo_num - 1))
			table->philos[i].right_fork = &table->forks[0];
		else
			table->philos[i].right_fork = &table->forks[i + 1];
		table->philos[i].have_eaten = 0;
		table->philos[i].last_meal_time = get_time();
		i++;
	}
	return (SUCC);
}

static void	parsing_table(t_table *table, char *av[], int ac)
{
	table->end_simu = 0;
	table->print_initial = 0;
	table->forks_initial = 0;
	table->err = 0;
	table->philo_num = ft_atoi(av[1]);
	table->die_time = ft_atoi(av[2]);
	table->eat_time = ft_atoi(av[3]);
	table->sleep_time = ft_atoi(av[4]);
	table->start_time = 0;
	table->think_time = set_think_time(table);
	if (ac == 6)
		table->must_eat = ft_atoi(av[5]);
	else
		table->must_eat = 0;
}

static int	init_mem_table(t_table *table)
{
	t_philo	*philos;

	if (!table)
		return (FAIL);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_num);
	if (!table->forks)
		return (FAIL);
	philos = malloc(sizeof(t_philo) * table->philo_num);
	if (!philos)
		return (clean_data(table, FAIL));
	table->philos = philos;
	table->threads = malloc(sizeof(pthread_t) * table->philo_num);
	if (!table->threads)
		return (clean_data(table, FAIL));
	return (SUCC);
}

static int	init_mutex_table(t_table *table)
{
	int	i;
	int	j;

	i = 0;
	if (pthread_mutex_init(&table->print_lock, NULL) != 0)
		return (clean_data(table, FAIL));
	table->print_initial = 1;
	while (i < table->philo_num)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			j = 0;
			table->forks_initial = 0;
			while (j < i)
			{
				pthread_mutex_destroy(&table->forks[j]);
				j++;
			}
			return (FAIL);
		}
		i++;
	}
	table->forks_initial = 1;
	i = 0;
	return (SUCC);
}
