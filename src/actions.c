/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:27:52 by scesar            #+#    #+#             */
/*   Updated: 2025/03/07 12:43:43 by scesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int    even_picks(t_philosopher *one_philo)
{
    pthread_mutex_lock(one_philo->r_fork);
    pthread_mutex_lock(&one_philo->table->time_mutex);
    if (a_philo_is_dead(one_philo->table))
    {
        pthread_mutex_unlock(one_philo->r_fork);
        pthread_mutex_unlock(&one_philo->table->time_mutex);
        return (0);
    }
    printf("%lld Philosopher %d has taken 1st fork.\n", one_philo->table->instant_time, one_philo->number);
    pthread_mutex_unlock(&one_philo->table->time_mutex);
    pthread_mutex_lock(one_philo->l_fork);
    pthread_mutex_lock(&one_philo->table->time_mutex);
    if (a_philo_is_dead(one_philo->table))
    {
        pthread_mutex_unlock(one_philo->r_fork);
        pthread_mutex_unlock(one_philo->l_fork);
        pthread_mutex_unlock(&one_philo->table->time_mutex);
        return (0);
    }
    printf("%lld Philosopher %d has taken 2nd fork.\n", one_philo->table->instant_time, one_philo->number);
    pthread_mutex_unlock(&one_philo->table->time_mutex);
    return (1);
}
int    odd_picks(t_philosopher *one_philo)
{
    pthread_mutex_lock(one_philo->l_fork);
    pthread_mutex_lock(&one_philo->table->time_mutex);
    if (a_philo_is_dead(one_philo->table))
    {
        pthread_mutex_unlock(one_philo->l_fork);
        pthread_mutex_unlock(&one_philo->table->time_mutex);
        return (0);
    }
    printf("%lld Philosopher %d has taken 1st fork.\n", one_philo->table->instant_time, one_philo->number);
    pthread_mutex_unlock(&one_philo->table->time_mutex);
    pthread_mutex_lock(one_philo->r_fork);
    pthread_mutex_lock(&one_philo->table->time_mutex);
    if (a_philo_is_dead(one_philo->table))
    {
        pthread_mutex_unlock(one_philo->l_fork);
        pthread_mutex_unlock(one_philo->r_fork);
        pthread_mutex_unlock(&one_philo->table->time_mutex);
        return (0);
    }
    printf("%lld Philosopher %d has taken 2nd fork.\n", one_philo->table->instant_time, one_philo->number);
    pthread_mutex_unlock(&one_philo->table->time_mutex);
    return (1);
}

int pick_up_forks(t_philosopher *one_philo)
{
    if (one_philo->number == 1 && one_philo->times_he_ate == 0)
        return(first_eat_first(one_philo));
    if(one_philo->number % 2 == 0)
        return(even_picks(one_philo));
    else
        return(odd_picks(one_philo));
}


int eating(t_philosopher *one_philo)
{
    pthread_mutex_lock(&one_philo->table->death_mutex);
    one_philo->last_meal = current_time() - one_philo->table->start_time;
    pthread_mutex_unlock(&one_philo->table->death_mutex);
    pthread_mutex_lock(&one_philo->table->time_mutex);
    if (a_philo_is_dead(one_philo->table))
    {
        pthread_mutex_unlock(one_philo->l_fork);
        pthread_mutex_unlock(one_philo->r_fork);
        pthread_mutex_unlock(&one_philo->table->time_mutex);
        return (0);
    }
    printf("%lld Philosopher %d is eating.\n", one_philo->table->instant_time, one_philo->number);
    pthread_mutex_unlock(&one_philo->table->time_mutex);
    usleep(one_philo->table->tte * 1000LL); // eating time
    one_philo->times_he_ate++;
    pthread_mutex_unlock(one_philo->r_fork);
    pthread_mutex_unlock(one_philo->l_fork);
    if (a_philo_is_dead(one_philo->table))
        return(0);
    return(1);
}

int sleeping(t_philosopher *one_philo)
{
    pthread_mutex_lock(&one_philo->table->time_mutex);
    if (a_philo_is_dead(one_philo->table))
    {
        pthread_mutex_unlock(&one_philo->table->time_mutex);
        return (0);
    }
    printf("%lld Philosopher %d is sleeping.\n", one_philo->table->instant_time, one_philo->number);
    pthread_mutex_unlock(&one_philo->table->time_mutex);
        usleep(one_philo->table->tts * 1000LL);  // sleeping time
    return(1);

    
}

int    first_eat_first(t_philosopher *first_philo)
{
    if (first_philo->times_he_ate == 0)
    {
        pthread_mutex_lock(first_philo->l_fork);
        printf("%lld Philosopher 1 has taken left fork first.\n", first_philo->table->instant_time);
        pthread_mutex_lock(first_philo->r_fork);
        printf("%lld Philosopher 1 has taken right fork first.\n", first_philo->table->instant_time);
        return(1);
    }
    else
        return(0);
}

// int even_picks(t_philosopher *one_philo)
// {
//     pthread_mutex_lock(one_philo->r_fork);
//     if (a_philo_is_dead(one_philo->table))
//     {
//         pthread_mutex_unlock(one_philo->r_fork);
//         return(0);
//     }
//     pthread_mutex_lock(&one_philo->table->time_mutex);
//     printf("%lld Philosopher %d picked up the right fork.\n", one_philo->table->instant_time, one_philo->number);
//     pthread_mutex_unlock(&one_philo->table->time_mutex);
//     pthread_mutex_lock(one_philo->l_fork);
//     if (a_philo_is_dead(one_philo->table))
//     {
//         pthread_mutex_unlock(one_philo->r_fork);
//         pthread_mutex_unlock(one_philo->l_fork);
//         return(0);
//     }
//     pthread_mutex_lock(&one_philo->table->time_mutex);
//     printf("%lld Philosopher %d picked up the left fork.\n", one_philo->table->instant_time, one_philo->number);
//     pthread_mutex_unlock(&one_philo->table->time_mutex);
//     return(1);
// }

// int odd_picks(t_philosopher *one_philo)
// {
//     pthread_mutex_lock(one_philo->l_fork);
//     if (a_philo_is_dead(one_philo->table))
//     {
//         pthread_mutex_unlock(one_philo->l_fork);
//         return(0);
//     }
//     pthread_mutex_lock(&one_philo->table->time_mutex);
//     printf("%lld Philosopher %d picked up the left fork.\n", one_philo->table->instant_time, one_philo->number);
//     pthread_mutex_unlock(&one_philo->table->time_mutex);
//     pthread_mutex_lock(one_philo->r_fork);
//     if (a_philo_is_dead(one_philo->table))
//     {
//         pthread_mutex_unlock(one_philo->l_fork);
//         pthread_mutex_unlock(one_philo->r_fork);
//         return(0);
//     }
//     pthread_mutex_lock(&one_philo->table->time_mutex);
//     printf("%lld Philosopher %d picked up the right fork.\n", one_philo->table->instant_time, one_philo->number);
//     pthread_mutex_unlock(&one_philo->table->time_mutex);
//     return(1);
// }

// int pick_up_forks(t_philosopher *one_philo)
// {
//     if (one_philo->number % 2 == 0)
//     {
//         if(!even_picks(one_philo))
//             return(0);
//     }
//     else
//     {
//         if(!odd_picks(one_philo))
//             return(0);
//     }
//     if (a_philo_is_dead(one_philo->table))
//     {
//         pthread_mutex_unlock(one_philo->r_fork);
//         pthread_mutex_unlock(one_philo->l_fork);
//         return(0);
//     }
//     return(1);
// }
