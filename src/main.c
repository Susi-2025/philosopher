/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:41:05 by vinguyen          #+#    #+#             */
/*   Updated: 2025/11/04 12:03:31 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av[])
{
	t_table	table;

	if (ac < 5 || ac > 6 || (check_args(ac, av) == 1))
		return (error_message(ARG_ERR, FAIL));
	ft_bzero(&table, sizeof(t_table));
	if (init_table(&table, av, ac) == FAIL)
		return (err_clean(&table, FAIL));
	if (init_philo(&table) == FAIL)
		return (err_clean(&table, FAIL));
	if (table.philo_num == 1)
		one_running(&table);
	else
		start_simulation(&table);
	clean_data(&table, 0);
	return (SUCC);
}

int	check_args(int ac, char *av[])
{
	int	i;

	if (!av[1])
		printf("Wrong arguments\n");
	i = 1;
	while (i < ac)
	{
		if (ft_valid_num(av[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

uint64_t	get_time(void)
{
	struct timeval	c_time;
	uint64_t		time;

	gettimeofday(&c_time, NULL);
	time = ((uint64_t)c_time.tv_sec * 1000) + ((uint64_t)c_time.tv_usec / 1000);
	return (time);
}

int	set_think_time(t_table *table)
{
	int	think_time;

	think_time = (table->die_time - table->eat_time - table->sleep_time) / 2;
	if (think_time < 0)
		think_time = 0;
	return (think_time);
}
