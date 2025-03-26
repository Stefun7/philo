/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:24:42 by scesar            #+#    #+#             */
/*   Updated: 2025/03/26 12:42:48 by scesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	even_picks(t_philosopher *one_philo)
{
	pthread_mutex_lock(one_philo->r_fork);
	if (!one_philo->table->smn_died)
		printf("%lld Philosopher %d has taken 1st fork.\n",
			one_philo->table->instant_time, one_philo->number);
	else
	{
		pthread_mutex_unlock(one_philo->r_fork);
		return (RIGHT);
	}
	pthread_mutex_lock(one_philo->l_fork);
	if (!one_philo->table->smn_died)
		printf("%lld Philosopher %d has taken 2nd fork.\n",
			one_philo->table->instant_time, one_philo->number);
	else
	{
		pthread_mutex_unlock(one_philo->l_fork);
		pthread_mutex_unlock(one_philo->r_fork);
		return (BOTH);
	}
	return (NONE);
}

int	odd_picks(t_philosopher *one_philo)
{
	pthread_mutex_lock(one_philo->l_fork);
	if (!one_philo->table->smn_died)
		printf("%lld Philosopher %d has taken 1st fork.\n",
			one_philo->table->instant_time, one_philo->number);
	else
	{
		pthread_mutex_unlock(one_philo->l_fork);
		return (LEFT);
	}
	if (one_philo->table->philo_nbr == 1)
		return (LEFT);
	pthread_mutex_lock(one_philo->r_fork);
	if (!one_philo->table->smn_died)
		printf("%lld Philosopher %d has taken 2nd fork.\n",
			one_philo->table->instant_time, one_philo->number);
	else
	{
		pthread_mutex_unlock(one_philo->r_fork);
		pthread_mutex_unlock(one_philo->l_fork);
		return (BOTH);
	}
	return (NONE);
}

int	pick_up_forks(t_philosopher *one_philo)
{
	int	fork_locked;

	if (one_philo->number % 2 == 1)
		fork_locked = odd_picks(one_philo);
	else
		fork_locked = even_picks(one_philo);
	if (one_philo->table->philo_nbr == 1)
	{
		pthread_mutex_unlock(one_philo->l_fork);
		return (NO);
	}
	if (fork_locked != NONE)
		return (NO);
	return (YES);
}

int	eating(t_philosopher *one_philo)
{
	if (!one_philo->table->smn_died)
		printf("%lld Philosopher %d is eating.\n",
			one_philo->table->instant_time, one_philo->number);
	else
	{
		pthread_mutex_unlock(one_philo->l_fork);
		pthread_mutex_unlock(one_philo->r_fork);
		return (NO);
	}
	pthread_mutex_lock(&one_philo->table->death_mutex);
	one_philo->last_meal = current_time() - one_philo->table->start_time;
	pthread_mutex_unlock(&one_philo->table->death_mutex);
	my_usleep(one_philo->table, (one_philo->table->tte));
	one_philo->times_he_ate++;
	pthread_mutex_unlock(one_philo->r_fork);
	pthread_mutex_unlock(one_philo->l_fork);
	if (one_philo->table->time_must_eat != NOT_MENTIONNED
		&& one_philo->times_he_ate == one_philo->table->time_must_eat)
	{
		one_philo->state = FULL;
		return (0);
	}
	if (one_philo->table->smn_died)
		return (0);
	return (YES);
}

int	sleeping(t_philosopher *one_philo)
{
	if (!one_philo->table->smn_died)
	{
		printf("%lld Philosopher %d is sleeping.\n",
			one_philo->table->instant_time, one_philo->number);
		my_usleep(one_philo->table, (one_philo->table->tts));
	}
	else
		return (NO);
	return (YES);
}

// int	odd_picks(t_philosopher *one_philo)
// {
// 	pthread_mutex_lock(one_philo->l_fork);
// 	if (one_philo->table->smn_died)
// 	{
// 		pthread_mutex_unlock(one_philo->l_fork);
// 		return (LEFT);
// 	}
// 	printf("%lld Philosopher %d has taken 1st fork.\n",
// 		one_philo->table->instant_time, one_philo->number);
// 	if (one_philo->table->philo_nbr == 1)
// 		return (LEFT);
// 	pthread_mutex_lock(one_philo->r_fork);
// 	if (one_philo->table->smn_died)
// 	{
// 		pthread_mutex_unlock(one_philo->r_fork);
// 		pthread_mutex_unlock(one_philo->l_fork);
// 		return (BOTH);
// 	}
// 	printf("%lld Philosopher %d has taken 2nd fork.\n",
// 		one_philo->table->instant_time, one_philo->number);
// 	return (NONE);
//
// int	even_picks(t_philosopher *one_philo)
// {
// 	pthread_mutex_lock(one_philo->r_fork);
// 	if (one_philo->table->smn_died)
// 	{
// 		pthread_mutex_unlock(one_philo->r_fork);
// 		return (RIGHT);
// 	}
// 	printf("%lld Philosopher %d has taken 1st fork.\n",
// 		one_philo->table->instant_time, one_philo->number);
// 	pthread_mutex_lock(one_philo->l_fork);
// 	if (one_philo->table->smn_died)
// 	{
// 		pthread_mutex_unlock(one_philo->l_fork);
// 		pthread_mutex_unlock(one_philo->r_fork);
// 		return (BOTH);
// 	}
// 	printf("%lld Philosopher %d has taken 2nd fork.\n",
// 		one_philo->table->instant_time, one_philo->number);
// 	return (NONE);
// }
// }