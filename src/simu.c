
#include "philo.h"

int start_simulation(t_table *table)
{
	unsigned int i;

	if (!table)
		return (FAIL);
	i = 0;
	// table->start_time = get_time();
	while (i < table->philo_num)
	{
		if (pthread_create(&table->threads[i], NULL
				, philo_routine, &table->philos[i]) != 0)
			return (clean_data(table), FAIL);
		i++;
	}
	table->start_time = get_time();
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

void	monitoring (t_table *table)
{
	int			i;
	uint64_t	wait_time;
	int			full_count;

	while (table->end_simu == 0)
	{
		i = 0;
		full_count = 0;
		while (i < table->philo_num && table->end_simu == 0)
		{
			wait_time = get_time() - table->philos[i].last_meal_time;
			if (wait_time > table->die_time)
			{
				table->end_simu = 1;
				print_message(table, table->philos[i].id, DIE);
			}
			if (table->must_eat != 0 && table->philos[i].have_eaten
						== table->must_eat)
					full_count++;
			i++;
		}
		if (table->must_eat != 0 && full_count == table->philo_num)
			table->end_simu = 1;
		usleep(1000);
	}
}
