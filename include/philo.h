/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:15:55 by vinguyen          #+#    #+#             */
/*   Updated: 2025/11/04 12:02:11 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define ARG_ERR "Arguments must be numeric and must be 5 or 6 args\n"
# define FORK_PICK "has taken a fork\n"
# define THINK "is thinking\n"
# define EAT "is eating\n"
# define SLEEP "is sleeping\n"
# define DIE "died\n"

# define FAIL 1
# define SUCC 0

typedef struct s_table	t_table;

typedef struct s_philo
{
	int					id;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	_Atomic uint64_t last_meal_time;
	_Atomic int have_eaten;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	int					philo_num;
	uint64_t			die_time;
	uint64_t			eat_time;
	uint64_t			sleep_time;
	uint64_t			think_time;
	int					must_eat;
	_Atomic uint64_t start_time;
	t_philo				*philos;
	pthread_t			*threads;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_lock;
	_Atomic int end_simu;
}						t_table;

// initial
int						init_table(t_table *table, char *av[], int ac);
int						init_philo(t_table *philo);
// simulation
int						start_simulation(t_table *table);
void					monitoring(t_table *table);
void					one_running(t_table *table);
int						check_die(t_table *table);
int						check_full(t_table *table);
// routine
void					*routine(void *arg);
void					safe_usleep(t_table *table, uint64_t duration);
// utility
int						ft_valid_num(char *s);
int						ft_atoi(char *s);
int						ft_strcmp(char *s1, char *s2);
void					ft_bzero(void *s, size_t n);
int						check_args(int ac, char *av[]);
uint64_t				get_time(void);
int						set_think_time(t_table *table);
// message
int						error_message(char *str, int code);
int						print_message(t_table *table, int id, char *str);
// clean
int						clean_data(t_table *table, int code);
int						err_clean(t_table *table, int code);
#endif
