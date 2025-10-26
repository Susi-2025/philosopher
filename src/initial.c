
#include "philo.h"

static	void    init_num_table(t_table *table, char *av[], int ac);
static	int		init_mem_table(t_table *table);
static	int		init_mutex_table(t_table *table);

int    init_table(t_table *table, char *av[], int ac)
{
	init_num_table(table, av, ac);
	if (init_mem_table(table) == FAIL)
		return (FAIL);
	if (init_mutex_table(table) == FAIL)
		return (FAIL);
	return (SUCC);
}

int	init_philo(t_table *table)
{
	unsigned	int	i;

	if (!table || !table->philos || !table->forks)
		return (FAIL);
	i = 0;
	while (i < table->philo_num)
	{
		table->philos[i].id = i + 1;
		table->philos[i].table = table;
		if (!(&table->forks[i]))
			return (FAIL);
		table->philos[i].left_fork = &table->forks[i];
		if (i == (table->philo_num - 1))
			table->philos[i].right_fork = &table->forks[0];
		else
			table->philos[i].right_fork = &table->forks[i + 1];
		table->philos[i].last_meal_time = get_time();
		i++;
	}
	return (SUCC);
}

static	void    init_num_table(t_table *table, char *av[], int ac)
{
    table->end_simu = 0;
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

static	int    init_mem_table(t_table *table)
{
	t_philo	*philos;
	
	if (!table)
		return (FAIL);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_num);
	if (!table->forks)
		return(FAIL);
	philos = malloc(sizeof(t_philo) * table->philo_num);
	if (!philos)
		return(clean_data(table), FAIL);
	table->philos = philos;
	table->threads = malloc(sizeof(pthread_t) * table->philo_num);
	if (!table->threads)
		return(clean_data(table), FAIL);
	return (SUCC);
}

static	int	init_mutex_table(t_table *table)
{
	unsigned int	i;

	i = 0;
	if (pthread_mutex_init(&table->print_lock, NULL) != 0)
		return(clean_data(table), FAIL);
	while (i < table->philo_num)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			i--;
			while (i > 0)
			{
				pthread_mutex_destroy(&table->forks[i]);
				i--;
			}
			return(clean_data(table), FAIL);
		}
		i++;
	}
	i = 0;
	return (SUCC);
}

static int	set_think_time(t_philo *philo)
{
	int		think_time;

	think_time = (philo->table->die_time - philo->table->eat_time
				- philo->table->sleep_time) / 2;

	return (think_time);
}