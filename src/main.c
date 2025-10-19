#include "philo.h"

int    main(int ac, char *av[])
{
    t_table table;

    if (ac < 5 || ac > 6 || (check_args(ac, av) == 1))
        return (error_message(ARG_ERR, FAIL));
    if (init_table(&table, av, ac) == FAIL)
        return (FAIL);
    if (init_philo(&table) == FAIL)
        return (FAIL);
    start_simulation(&table);
    return (SUCC);
}