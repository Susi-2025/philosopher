
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