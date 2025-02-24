/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephen <stephen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:44:51 by stephen           #+#    #+#             */
/*   Updated: 2025/02/24 11:01:02 by stephen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void    check_if_death(void *the_table)
{
    t_table *table;
    long long now;
    int i;

    table = (t_table*) the_table;
    while(1)
    {
        i = 0;
        while(i < table->philo_nbr)
        {
            now = current_time();
            if ((table->time_must_eat != NOT_MENTIOENNED) && (now - table->philos[i].last_meal > table->time_must_eat))
            {
                printf("Philosopher number %d died at %lld ms\n", table->philos[i].number, now);
                return(NULL);
            }
            i++;
        }
        usleep(1000); // avoid CPU overuse ??
    }
}

void    start_dinner(t_table *table)
{
    int i;
    pthread_t monitoring_death;

    i = 0;
    while(i < table->philo_nbr)
    {
        pthread_create(&table->philos[i].thread, NULL, routine, &table->philos[i]);
        i++;
    }
    monitoring_death = pthread_create(&monitoring_death, NULL, check_if_death, (void *) table);
    i = 0;
    while(i < table->philo_nbr)
    {
        pthread_join(&table->philos[i].thread, NULL);
        i++;
    }
    return;
}

void    routine(void *this_philo)
{
    t_philosopher *one_philo;

    one_philo = (t_philosopher *)this_philo;
    while(1)
    {
        if (one_philo->number % 2 == 0)
        {
            pthread_mutex_lock(one_philo->r_fork);
            printf("Philosopher %d picked up the right fork.\n", one_philo->number);
            pthread_mutex_lock(one_philo->l_fork);
            printf("Philosopher %d picked up the left fork.\n", one_philo->number);
        }
        else
        {
            pthread_mutex_lock(one_philo->l_fork);
            printf("Philosopher %d picked up the left fork.\n", one_philo->number);
            pthread_mutex_lock(one_philo->r_fork);
            printf("Philosopher %d picked up the right fork.\n", one_philo->number);
        }
        one_philo->last_meal = current_time();
        printf("Philosopher %d is eating.\n", one_philo->number);
        usleep(one_philo->table->tte * 1000LL); // Simulate eating

        pthread_mutex_unlock(one_philo->r_fork);
        pthread_mutex_unlock(one_philo->l_fork);
        printf("Philosopher %d put down the forks and is sleeping\n", one_philo->number);
        usleep(one_philo->table->tts * 1000LL);  // Simulate sleeping
        
        printf("Philosopher %d is thinking...\n", one_philo->number);
        usleep(1000);
    }
    return;
}
