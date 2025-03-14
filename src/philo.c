/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:17:21 by scesar            #+#    #+#             */
/*   Updated: 2025/03/14 12:46:14 by scesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int starvation(t_philosopher *philo)
{
    long long now;

    now = current_time() - philo->table->start_time;
    pthread_mutex_lock(&philo->table->death_mutex); // **
    if (now - philo->last_meal > philo->table->ttd)
    {
        printf("Philosopher number %d died at %lld ms\n",philo->number, now);
        philo->state = DEATH; //maybe not necessary
        pthread_mutex_unlock(&philo->table->death_mutex);
        philo->table->smn_died = YES;
        return(YES);
    }
    pthread_mutex_unlock(&philo->table->death_mutex);
    return(NO);
}

int a_philo_is_dead(t_table *table)
{
    return(table->smn_died);
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
            table->instant_time = current_time() - table->start_time;
            if (starvation(&table->philos[i]))
            {
                return(NULL);
            }
        }
        usleep(1000); // avoid CPU overuse ??, make an adaptative one
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
        {
            printf("Philo nmbr %d stopped 1\n", one_philo->number);
            return(NULL);
        }
        if (!pick_up_forks(one_philo))
        {
            printf("Philo nmbr %d stopped 2\n", one_philo->number);
            return(NULL);
        }
        if (!eating(one_philo))
        {
            printf("Philo nmbr %d stopped 3\n", one_philo->number);
            return(NULL);
        }
        if (!sleeping(one_philo))
        {
            printf("Philo nmbr %d stopped 4\n", one_philo->number);
            return(NULL);
        }
        printf("%lld Philosopher %d is thinking...\n", one_philo->table->instant_time, one_philo->number);
    }
    return(NULL);
}
