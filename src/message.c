
#include "philo.h"

int error_message(char *str, int code)
{
    printf("%s\n", str);
    return (code);
}

int    print_message(t_table *table, int id, char *str)
{
    uint64_t    time_display;

    if (pthread_mutex_lock(&table->print_lock) != SUCC)
        return (FAIL);
    time_display = get_time() - table->start_time;
    printf("%lu %d %s", time_display, id, str);
    if (pthread_mutex_unlock(&table->print_lock) != SUCC)
        return (FAIL);
    return (SUCC);
}