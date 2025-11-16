/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:41:16 by vinguyen          #+#    #+#             */
/*   Updated: 2025/11/16 10:33:12 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_message(char *str, int code)
{
	printf("%s\n", str);
	return (code);
}

int	print_message(t_table *table, int id, char *str)
{
	uint64_t	time_display;
	int			should_print;

	should_print = 1;
	if (table->end_simu == 1 && (ft_strcmp(str, DIE) != 0 || table->err == 1))
		should_print = 0;
	if (should_print)
	{
		pthread_mutex_lock(&table->print_lock);
		time_display = get_time() - table->start_time;
		printf("%lu %d %s", time_display, id, str);
		pthread_mutex_unlock(&table->print_lock);
	}
	if (should_print)
		return (SUCC);
	else
		return (FAIL);
}

void	safe_usleep(t_table *table, uint64_t duration)
{
	uint64_t	start;

	start = get_time();
	while (!table->end_simu && (get_time() - start) < duration)
		usleep(500);
}
