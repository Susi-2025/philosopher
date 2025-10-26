
#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <limits.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdint.h>
# include <sys/time.h>
# include <unistd.h>

# define ARG_ERR    "Arguments must be numeric and must be 5 or 6 args\n"
# define FORK_PICK "has taken a fork\n"
# define THINK      "is thinking\n"
# define EAT        "is eating\n"
# define SLEEP      "is sleeping\n"
# define DIE        "died\n"

# define FAIL 1
# define SUCC 0

typedef struct s_table t_table;

typedef struct  s_philo
{
    unsigned    int id;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    uint64_t        last_meal_time;
    t_table         *table;
}   t_philo;

typedef struct  s_table
{
    unsigned    int philo_num;
    unsigned    int die_time;
    unsigned    int eat_time;
    unsigned    int sleep_time;
    unsigned    int think_time;
    unsigned    int must_eat;
    unsigned    int end_simu;
    uint64_t        start_time;

    t_philo         *philos;
    pthread_t       *threads;
    pthread_mutex_t *forks;
    pthread_mutex_t print_lock;
}   t_table;

// initial
int init_table(t_table *table, char *av[], int ac);
int init_philo(t_table *philo);

// simulation
int	start_simulation(t_table *table);

// routine
void	*philo_routine(void *arg);

//utility
int ft_valid_num(char *s);
int ft_atoi(char *s);
int check_args(int ac, char *av[]);
uint64_t   get_time(void);

//message
int error_message(char *str, int code);
int print_message(t_table *table, int id, char *str);

// clean
void	clean_data(t_table *table);
#endif