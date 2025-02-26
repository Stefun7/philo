/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:27:52 by scesar            #+#    #+#             */
/*   Updated: 2025/02/26 18:54:52 by scesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int even_picks(t_philosopher *one_philo)
{
    pthread_mutex_lock(one_philo->r_fork);
    printf("Philosopher %d picked up the right fork.\n", one_philo->number);
    if (a_philo_is_dead(one_philo->table))
    {
        pthread_mutex_unlock(one_philo->r_fork);
        return(0);
    }
    pthread_mutex_lock(one_philo->l_fork);
    printf("Philosopher %d picked up the left fork.\n", one_philo->number);
    return(1);
}

int odd_picks(t_philosopher *one_philo)
{
    pthread_mutex_lock(one_philo->l_fork);
    printf("Philosopher %d picked up the left fork.\n", one_philo->number);
    if (a_philo_is_dead(one_philo->table))
    {
        pthread_mutex_unlock(one_philo->l_fork);
        return(0);
    }
    pthread_mutex_lock(one_philo->r_fork);
    printf("Philosopher %d picked up the right fork.\n", one_philo->number);
    return(1);
}

int pick_up_forks(t_philosopher *one_philo)
{
    if (one_philo->number % 2 == 0)
    {
        if(!even_picks(one_philo))
            return(0);
    }
    else
    {
        if(!odd_picks(one_philo))
            return(0);
    }
    if (a_philo_is_dead(one_philo->table))
    {
        pthread_mutex_unlock(one_philo->r_fork);
        pthread_mutex_unlock(one_philo->l_fork);
        return(0);
    }
    return(1);
}
int eating(t_philosopher *one_philo)
{
    pthread_mutex_lock(&one_philo->table->death_mutex);
    one_philo->last_meal = current_time();
    pthread_mutex_unlock(&one_philo->table->death_mutex);
    printf("Philosopher %d is eating.\n", one_philo->number);
    usleep(one_philo->table->tte * 1000LL); // eating time
    pthread_mutex_unlock(one_philo->r_fork);
    pthread_mutex_unlock(one_philo->l_fork);
    printf("Philosopher %d put down the forks\n", one_philo->number);
    if (a_philo_is_dead(one_philo->table))
        return(0);
    else
        return(1);
}

int sleeping(t_philosopher *one_philo)
{
    printf("Philosopher %d is sleeping\n", one_philo->number);
        usleep(one_philo->table->tts * 1000LL);  // sleeping time
    return(1);
}
