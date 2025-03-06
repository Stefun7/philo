/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:11:11 by stephen           #+#    #+#             */
/*   Updated: 2025/03/06 14:45:22 by scesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include "../Libft/inc/libft.h"
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
#include <limits.h>

# define NOT_MENTIONNED INT_MIN
# define THREAD_CREATION_FAILURE INT_MAX
# define MALLOC_FAILURE 2
# define DEATH 0
# define ALIVE 1
# define NO 0
# define YES 1

typedef struct s_table t_table;

typedef struct s_philosopher
{
    int number;
    long long last_meal;
    int times_left_to_eat;
    int state;
    pthread_t thread;
    pthread_mutex_t *l_fork;
    pthread_mutex_t *r_fork;
    t_table *table;
}   t_philosopher;

typedef struct s_table
{
    int philo_nbr;
    t_philosopher *philos;
    pthread_mutex_t *forks;
    int ttd;
    int tte;
    int tts;
    int time_must_eat;
    int smn_died;
    long long start_time;
    long long instant_time;
    pthread_mutex_t time_mutex;
    pthread_mutex_t death_mutex;
}   t_table;

// philo
int a_philo_is_dead(t_table *table);
void    *monitor_routine(void *the_table);
void    start_dinner(t_table *table);
void    *routine(void *this_philo);
int starvation(t_philosopher *philo);

// main
void    init_dinner(int ac, char **av, t_table *table);
void    init_philos(int ac, t_table *table);
void    init_table(int ac, char **av, t_table *table);

// actions
int even_picks(t_philosopher *one_philo);
int odd_picks(t_philosopher *one_philo);
int pick_up_forks(t_philosopher *one_philo);
int eating(t_philosopher *one_philo);
int sleeping(t_philosopher *one_philo);

// utils
long long current_time(void);
int valid_number(char *number);
long long	my_atoi(const char *str);

#endif