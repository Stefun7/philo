/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:25:04 by scesar            #+#    #+#             */
/*   Updated: 2025/03/21 18:21:28 by scesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include "../Libft/inc/libft.h"
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <stdatomic.h>

# define NOT_MENTIONNED INT_MIN

# define DEAD 0
# define ALIVE 1
# define FULL INT_MAX

# define NO 0
# define YES 1

# define LEFT 0
# define RIGHT 1
# define BOTH 2
# define NONE 3

typedef struct s_table	t_table;

typedef struct s_philosopher
{
	int					number;
	long long			last_meal;
	_Atomic long long	times_he_ate;
	_Atomic int			state;
	pthread_t			thread;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	t_table				*table;
}				t_philosopher;

typedef struct s_table
{
	int					philo_nbr;
	t_philosopher		*philos;
	pthread_mutex_t		*forks;
	int					ttd;
	int					tte;
	int					tts;
	long long			time_must_eat;
	_Atomic int			smn_died;
	_Atomic long long	start_time;
	_Atomic long long	instant_time;
	pthread_mutex_t		death_mutex;
}				t_table;

// philo
void		*monitor_routine(void *the_table);
int			start_dinner(t_table *table);
void		*routine(void *this_philo);
int			starvation(t_philosopher *philo);

// main
void		init_dinner(int ac, char **av, t_table *table);
void		init_philos(int ac, t_table *table);
void		init_table(int ac, char **av, t_table *table);
void		first_picks_first(t_philosopher *first_philo);

// actions
int			even_picks(t_philosopher *one_philo);
int			odd_picks(t_philosopher *one_philo);
int			pick_up_forks(t_philosopher *one_philo);
int			eating(t_philosopher *one_philo);
int			sleeping(t_philosopher *one_philo);

// utils
long long	current_time(void);
int			valid_number(char *number);
long long	my_atoll(const char *str);
void		my_usleep(t_table *table, long long time);
int			exit_dinner(t_table *table, int error_type, int threads_created);

#endif
