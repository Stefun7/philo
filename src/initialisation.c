/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:25:30 by scesar            #+#    #+#             */
/*   Updated: 2025/03/21 17:25:33 by scesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	init_philos(int ac, t_table *table)
{
	int	nbr;

	nbr = -1;
	while (++nbr < table->philo_nbr)
		pthread_mutex_init(&table->forks[nbr], NULL);
	nbr = -1;
	while (++nbr < table->philo_nbr)
	{
		table->philos[nbr].times_he_ate = 0;
		table->philos[nbr].state = ALIVE;
		table->philos[nbr].number = nbr + 1;
		table->philos[nbr].table = table;
		table->philos[nbr].l_fork = &table->forks[nbr];
		table->philos[nbr].r_fork = &table->forks[(nbr + 1) % table->philo_nbr]; //philo_nbr is for the last philo to get the right r_fork
	}
}

void	init_table(int ac, char **av, t_table *table)
{
	table->philo_nbr = my_atoll(av[1]);
	table->ttd = my_atoll(av[2]);
	table->tte = my_atoll(av[3]);
	table->tts = my_atoll(av[4]);
	if (ac == 6)
		table->time_must_eat = my_atoll(av[5]);
	else
		table->time_must_eat = NOT_MENTIONNED;
	table->philos = malloc(sizeof(t_philosopher) * table->philo_nbr);
	if (!table->philos)
		return ;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_nbr);
	if (!table->forks)
	{
		free(table->philos);
		return ;
	}
	pthread_mutex_init(&table->death_mutex, NULL);
	table->smn_died = NO;
}

void	init_dinner(int ac, char **av, t_table *table)
{
	init_table(ac, av, table);
	init_philos(ac, table);
}

int	start_dinner(t_table *table)
{
	pthread_t	monitor_death;
	long long	error_type;
	int			i;

	table->start_time = current_time();
	table->instant_time = current_time() - table->start_time;
	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_create(&table->philos[i].thread,
			NULL, routine, &table->philos[i]);
		table->philos[i].last_meal = 0;
		i++;
	}
	pthread_create(&monitor_death, NULL, monitor_routine, (void *) table);
	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor_death, NULL);
	free(table->philos);
	free(table->forks);
	return (1);
}
