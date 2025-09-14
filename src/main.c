#include "philo.h"

int    main(int ac, char *av[])
{
    t_philo *philo;

    if (ac < 5 || ac > 6)
    {
        printf("Number of arguments is unsuitable\n");
        return (1);
    }
    if (check_arguments(ac, av) == 1)
    {
        printf("Arguments is non numeric\n");
        return (1);
    }
    init_philo(philo, av);
    if (ac == 6)
        philo->num_must_eat = ft_atoi(av[5]);
    else
        philo->num_must_eat = 0;
    return (0);
}

static  int check_arguments(int ac, char *av[])
{
    int i;

    if (!av[0])
        printf("Wrong arguments\n");
    i = 1;
    while (i < ac)
    {
        if (ft_valid_pos_num(av[i]) == 1)
            return (1);
        i++;
    }
    return (0);
}

static void    init_philo(t_philo *philo, char *av[])
{
    philo->num_person = ft_atoi(av[1]);
    philo->time_to_die = ft_atoi(av[2]);
    philo->time_to_eat = ft_atoi(av[3]);
    philo->time_to_sleep = ft_atoi(av[4]);
}