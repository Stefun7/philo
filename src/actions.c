/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:27:52 by scesar            #+#    #+#             */
/*   Updated: 2025/03/14 13:54:40 by scesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int even_picks(t_philosopher *one_philo)
{
    pthread_mutex_lock(one_philo->r_fork);
    if (a_philo_is_dead(one_philo->table))
    {
        pthread_mutex_unlock(one_philo->r_fork);
        return (RIGHT);
    }
    printf("%lld Philosopher %d has taken 1st fork.\n", one_philo->table->instant_time, one_philo->number);

    pthread_mutex_lock(one_philo->l_fork);
    if (a_philo_is_dead(one_philo->table))
    {
        pthread_mutex_unlock(one_philo->l_fork);
        pthread_mutex_unlock(one_philo->r_fork);
        return (BOTH);
    }
    printf("%lld Philosopher %d has taken 2nd fork.\n", one_philo->table->instant_time, one_philo->number);
    return (NONE);
}

int odd_picks(t_philosopher *one_philo)
{
    pthread_mutex_lock(one_philo->l_fork);
    if (a_philo_is_dead(one_philo->table))
    {
        pthread_mutex_unlock(one_philo->l_fork);
        return (LEFT);
    }
    printf("%lld Philosopher %d has taken 1st fork.\n", one_philo->table->instant_time, one_philo->number);
    if (one_philo->table->philo_nbr == 1)
        return (LEFT);

    pthread_mutex_lock(one_philo->r_fork);
    if (a_philo_is_dead(one_philo->table))
    {
        pthread_mutex_unlock(one_philo->r_fork);
        pthread_mutex_unlock(one_philo->l_fork);
        return (BOTH);
    }
    printf("%lld Philosopher %d has taken 2nd fork.\n", one_philo->table->instant_time, one_philo->number);
    return (NONE);
}


int pick_up_forks(t_philosopher *one_philo)
{
    int fork_locked;

    if (one_philo->number == 1 && one_philo->times_he_ate == 0)
        return (YES);
    if (one_philo->table->philo_nbr == 1)
    {
        pthread_mutex_unlock(one_philo->l_fork);
        return (NO);
    }

    if (one_philo->number % 2 == 0)
        fork_locked = even_picks(one_philo);
    else
        fork_locked = odd_picks(one_philo);

    if (fork_locked != NONE)
        return (NO);

    return (YES);
}

int eating(t_philosopher *one_philo)
{
    if (a_philo_is_dead(one_philo->table))
    {
        pthread_mutex_unlock(one_philo->l_fork);
        pthread_mutex_unlock(one_philo->r_fork);
        return (0);
    }
    printf("%lld Philosopher %d is eating.\n", one_philo->table->instant_time, one_philo->number);
    pthread_mutex_lock(&one_philo->table->death_mutex);
    one_philo->last_meal = current_time() - one_philo->table->start_time;
    pthread_mutex_unlock(&one_philo->table->death_mutex);
    // usleep(one_philo->table->tte * 1000LL); // eating time
    my_usleep(one_philo->table, (one_philo->table->tte));
    // printf("time after eating : %lld\n", one_philo->table->instant_time);
    one_philo->times_he_ate++;
    pthread_mutex_unlock(one_philo->r_fork);
    pthread_mutex_unlock(one_philo->l_fork);
    // printf("---philo nbr %d dropped forks---\n", one_philo->number);
    if (a_philo_is_dead(one_philo->table))
        return(0);
    return(1);
}

int sleeping(t_philosopher *one_philo)
{
    if (a_philo_is_dead(one_philo->table))
    {
        return (0);
    }
    printf("%lld Philosopher %d is sleeping.\n", one_philo->table->instant_time, one_philo->number);
    // usleep(one_philo->table->tts * 1000LL);  // sleeping time
    my_usleep(one_philo->table, (one_philo->table->tts));
    // printf(" philo %d state :%d\n",one_philo->number, one_philo->state);
    if (a_philo_is_dead(one_philo->table))
        return(0);
    return(1);

    
}



// int even_picks(t_philosopher *one_philo)
// {
//     pthread_mutex_lock(one_philo->r_fork);
//     if (a_philo_is_dead(one_philo->table)
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
