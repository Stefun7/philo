/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:24:28 by scesar            #+#    #+#             */
/*   Updated: 2025/03/25 17:44:50 by scesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	everyone_ate(t_table *table)
{
	int	i;
	int	all_who_ate;

	i = 0;
	all_who_ate = 0;
	while (i < table->philo_nbr)
	{
		if (table->philos[i].state == FULL)
			all_who_ate++;
		i ++;
	}
	if (all_who_ate == table->philo_nbr)
		return (YES);
	else
		return (NO);
}

int	starvation(t_philosopher *philo)
{
	long long	now;

	now = current_time() - philo->table->start_time;
	pthread_mutex_lock(&philo->table->death_mutex);
	if (now - philo->last_meal > philo->table->ttd)
	{
		printf("Philosopher number %d died at %lld ms\n", philo->number, now);
		philo->state = DEAD;
		philo->table->smn_died = YES;
		pthread_mutex_unlock(&philo->table->death_mutex);
		return (YES);
	}
	pthread_mutex_unlock(&philo->table->death_mutex);
	return (NO);
}

void	*monitor_routine(void *the_table)
{
	t_table	*table;
	int		i;

	table = (t_table *) the_table;
	while (1)
	{
		i = -1;
		while (++i < table->philo_nbr)
		{
			table->instant_time = current_time() - table->start_time;
			if (starvation(&table->philos[i]))
				return (NULL);
		}
		if (everyone_ate(table) == YES)
		{
			printf("Hope everyone enjoyed their meal :)\nSee you soon !!\n");
			table->smn_died = YES;
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

void	*routine(void *this_philo)
{
	t_philosopher	*one_philo;

	one_philo = (t_philosopher *)this_philo;
	if (one_philo->times_he_ate == 0 && one_philo->number != 1)
		usleep(500);
	while (1)
	{
		if (one_philo->table->smn_died)
			return (NULL);
		if (!pick_up_forks(one_philo))
			return (NULL);
		if (!eating(one_philo))
			return (NULL);
		if (one_philo->table->time_must_eat != NOT_MENTIONNED
			&& one_philo->times_he_ate == one_philo->table->time_must_eat)
			one_philo->state = FULL;
		if (!sleeping(one_philo))
			return (NULL);
		if (!one_philo->table->smn_died)
			printf("%lld Philosopher %d is thinking...\n",
				one_philo->table->instant_time, one_philo->number);
		else
			return (NULL);
	}
	return (NULL);
}
