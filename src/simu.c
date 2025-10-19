
#include "philo.h"

int	start_simulation(t_table *table)
{
	unsigned	int	i;

	if (!table)
		return (FAIL);
	i = 0;
	while (i < table->philo_num)
	{
		if(pthread_create(&table->threads[i], NULL, philo_routine, &table->philos[i]) != 0)
			return(clean_data(table), FAIL);
		i++;
	}
	table->start_time = get_time();
	//monitoring(table);
	i = 0;
	while (i < table->philo_num)
	{
		if(pthread_join(table->threads[i], NULL) != 0)
			return(clean_data(table), FAIL);
		i++;
	}
	return (SUCC);
}

