#include "philo.h"

int main(int ac, char *av[])
{
    t_table table;

    if (ac < 5 || ac > 6 || (check_args(ac, av) == 1))
        return (error_message(ARG_ERR, FAIL));
    if (init_table(&table, av, ac) == FAIL)
        return (err_clean(&table, FAIL));
    if (init_philo(&table) == FAIL)
        return (err_clean(&table, FAIL));
    start_simulation(&table);
    clean_data(&table);
    return (SUCC);
}

int check_args(int ac, char *av[])
{
    int i;

    if (!av[0])
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

uint64_t get_time(void)
{
    struct timeval c_time;
    uint64_t time;

    gettimeofday(&c_time, NULL);
    time = ((uint64_t)c_time.tv_sec * 1000) + ((uint64_t)c_time.tv_usec / 1000);
    return (time);
}
