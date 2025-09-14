
#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <limits.h>

typedef struct  s_philo
{
    unsigned    int num_person;
    unsigned    int time_to_die;
    unsigned    int time_to_eat;
    unsigned    int time_to_sleep;
    unsigned    int num_must_eat;
}   t_philo;

int ft_valid_pos_num(char *s);
int ft_atoi(char *s);

#endif