/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:44:51 by stephen           #+#    #+#             */
/*   Updated: 2025/02/26 19:09:49 by scesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int a_philo_is_dead(t_table *table)
{
    int state;

    pthread_mutex_lock(&table->death_mutex);
    state = table->smn_died;
    pthread_mutex_unlock(&table->death_mutex);
    return(state);
}

void    *monitor_routine(void *the_table)
{
    t_table *table;
    long long now;
    int i;

    table = (t_table*) the_table;
    while(1)
    {
        i = -1;
        while(++i < table->philo_nbr)
        {
            if (a_philo_is_dead(table))
                return(NULL);
            now = current_time();
            pthread_mutex_lock(&table->death_mutex);
            if (now - table->philos[i].last_meal > table->ttd)
            {
                printf("Philosopher number %d died at %lld ms\n", table->philos[i].number, now);
                table->smn_died = 1;
                pthread_mutex_unlock(&table->death_mutex);
                return(NULL);
            }
            pthread_mutex_unlock(&table->death_mutex);
        }
        usleep(5000); // avoid CPU overuse ??
    }
    return(NULL);
}

void    start_dinner(t_table *table)
{
    int i;
    pthread_t monitor_death;

    if(pthread_create(&monitor_death, NULL, monitor_routine, (void *) table) != 0)
        exit(THREAD_CREATION_FAILURE);
    i = 0;
    while(i < table->philo_nbr)
    {
        if(pthread_create(&table->philos[i].thread, NULL, routine, &table->philos[i]) != 0)
            exit(THREAD_CREATION_FAILURE);
        i++;
    }
    i = 0;
    while(i < table->philo_nbr)
    {
        pthread_join(table->philos[i].thread, NULL);
        i++;
    }
    pthread_join(monitor_death, NULL);
    return;
}

void    *routine(void *this_philo)
{
    t_philosopher *one_philo;

    one_philo = (t_philosopher *)this_philo;
    while(1)
    {
        if (a_philo_is_dead(one_philo->table))
            return(NULL);
        if(!pick_up_forks(one_philo))
            return(NULL);
        if(!eating(one_philo))
            return(NULL);
        sleeping(one_philo);
        if (a_philo_is_dead(one_philo->table))
            return(NULL);
        printf("Philosopher %d is thinking...\n", one_philo->number);
    }
    return(NULL);
}
