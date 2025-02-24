/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephen <stephen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:11:11 by stephen           #+#    #+#             */
/*   Updated: 2025/02/18 17:57:36 by stephen          ###   ########.fr       */
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
    pthread_mutex_t death_mutex;
}   t_table;

typedef struct s_philosopher
{
    int number;
    long long last_meal;
    int times_left_to_eat;
    pthread_t thread;
    pthread_mutex_t *l_fork;
    pthread_mutex_t *r_fork;
    t_table *table;
}   t_philosopher;

// utils
long long current_time(void);

#endif