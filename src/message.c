/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:41:16 by vinguyen          #+#    #+#             */
/*   Updated: 2025/11/02 17:44:21 by vinguyen         ###   ########.fr       */
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

	pthread_mutex_lock(&table->print_lock);
	if (table->end_simu == 1 && ft_strcmp(str, DIE) != 0)
	{
		pthread_mutex_unlock(&table->print_lock);
		return (FAIL);
	}
	time_display = get_time() - table->start_time;
	printf("%lu %d %s", time_display, id, str);
	pthread_mutex_unlock(&table->print_lock);
	return (SUCC);
}
