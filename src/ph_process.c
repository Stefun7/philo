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
            pthread_mutex_lock(&table->death_mutex);
            if (now - table->philos[i].last_meal > table->ttd)
            {
                printf("Philosopher number %d died at %lld ms\n", table->philos[i].number, now);
                table->smn_died = 1;
                pthread_mutex_unlock(&table->death_mutex);
                return;
            }
            pthread_mutex_unlock(&table->death_mutex);
            i++;
        }
        usleep(1000); // avoid CPU overuse ??
    }
}

void    start_dinner(t_table *table)
{
    int i;
    pthread_t monitor_death;

    i = 0;
    while(i < table->philo_nbr)
    {
        if(pthread_create(&table->philos[i].thread, NULL, routine, &table->philos[i]) != 0)
            exit(THREAD_CREATION_FAILURE);
        i++;
    }
    if(pthread_create(&monitor_death, NULL, check_if_death, (void *) table) != 0)
        exit(THREAD_CREATION_FAILURE);
    i = 0;
    while(i < table->philo_nbr)
    {
        pthread_join(&table->philos[i].thread, NULL);
        i++;
    }
    pthread_join(&monitor_death, NULL);
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
            pthread_mutex_lock(&one_philo->table->death_mutex);
            if (one_philo->table->smn_died)
            {
                pthread_mutex_unlock(&one_philo->table->death_mutex);
                return;  // Exit routine properly
            }
            pthread_mutex_unlock(&one_philo->table->death_mutex);                       //mk it a function and test it before every action

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

        usleep(1000); //necessary ?

        pthread_mutex_unlock(one_philo->r_fork);
        pthread_mutex_unlock(one_philo->l_fork);
        printf("Philosopher %d put down the forks and is sleeping\n", one_philo->number);
        usleep(one_philo->table->tts * 1000LL);  // Simulate sleeping
        
        printf("Philosopher %d is thinking...\n", one_philo->number);
        usleep(1000);
    }
    return;
}
