/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:17:21 by scesar            #+#    #+#             */
/*   Updated: 2025/03/05 18:40:45 by scesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int starvation(t_philosopher *philo)
{
    long long now;

    now = current_time();
    pthread_mutex_lock(&philo->table->death_mutex);
    if (now - philo->last_meal > philo->table->ttd)
    {
        printf("Philosopher number %d died at %lld ms\n",philo->number, now);
        philo->table->smn_died = YES;
        pthread_mutex_unlock(&philo->table->death_mutex);
        return(1);
    }
    pthread_mutex_unlock(&philo->table->death_mutex);
    return(0);
}

int a_philo_is_dead(t_table *table)
{
    int philos_state;

    pthread_mutex_lock(&table->death_mutex);
    philos_state = table->smn_died;
    pthread_mutex_unlock(&table->death_mutex);
    return(philos_state);
}

void    *monitor_routine(void *the_table)
{
    t_table *table;
    int i;

    table = (t_table*) the_table;
    while(1)
    {
        i = -1;
        while(++i < table->philo_nbr)
        {
            if (a_philo_is_dead(table))
                return(NULL);
        }
        usleep(5000); // avoid CPU overuse ??
    }
    return(NULL);
}

void    *routine(void *this_philo)
{
    t_philosopher *one_philo;

    one_philo = (t_philosopher *)this_philo;
    while(1)
    {
        if (a_philo_is_dead(one_philo->table))
            return(NULL);
        if (!pick_up_forks(one_philo))
            return(NULL);
        if (!eating(one_philo))
            return(NULL);
        sleeping(one_philo);
        if (a_philo_is_dead(one_philo->table))
            return(NULL);
        printf("Philosopher %d is thinking...\n", one_philo->number);
    }
    return(NULL);
}

void    start_dinner(t_table *table)
{
    int i;
    pthread_t monitor_death;

    table->start_time = current_time();
    i = 0;
    while(i < table->philo_nbr)
    {
        if(pthread_create(&table->philos[i].thread, NULL, routine, &table->philos[i]) != 0)
            exit(THREAD_CREATION_FAILURE);
        table->philos[i].last_meal = table->start_time;
        i++;
    }
    if(pthread_create(&monitor_death, NULL, monitor_routine, (void *) table) != 0) //see if it should be placed after the philo threads
        exit(THREAD_CREATION_FAILURE);//can't exit
    i = 0;
    while(i < table->philo_nbr)
    {
        pthread_join(table->philos[i].thread, NULL);//can't exit
        i++;
    }
    pthread_join(monitor_death, NULL);
    return;
}

