/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:33:51 by scesar            #+#    #+#             */
/*   Updated: 2025/03/21 12:36:09 by scesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"


void    init_philos(int ac, t_table *table)
{
    int nbr;

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

void    init_table(int ac, char **av, t_table *table)
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
        return;
    table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_nbr);
    if (!table->forks)
    {
        free(table->philos);
        return;
    }
    pthread_mutex_init(&table->death_mutex, NULL);
    table->smn_died = NO;
    // printf("philo nbr : %d \nttd : %d \ntte : %d \ntts : %d \ntme : %lld\n",
    // table->philo_nbr, table->ttd, table->tte, table->tts, table->time_must_eat);
}

void    init_dinner(int ac, char **av, t_table *table)
{
    init_table(ac, av, table);
    init_philos(ac, table);
}


int    start_dinner(t_table *table)
{
    int i;
    pthread_t monitor_death;
    long long error_type;

    table->start_time = current_time();
    table->instant_time = current_time() - table->start_time;
    i = 0;
    while(i < table->philo_nbr)
    {
        pthread_create(&table->philos[i].thread, NULL, routine, &table->philos[i]);
        table->philos[i].last_meal = 0;
        i++;
    }
    pthread_create(&monitor_death, NULL, monitor_routine, (void *) table);
    i = 0;
    while(i < table->philo_nbr)
    {
        // printf("Joining Philosopher %d at %p\n", table->philos[i].number, &table->philos[i]);
        pthread_join(table->philos[i].thread, NULL);
        // printf("---- Philosopher %d has exited ----\n", table->philos[i].number);
        i++;
    }
    pthread_join(monitor_death, NULL);
    // printf("----monitor routine joined-----\n");
    free(table->philos);
    free(table->forks);
    return(1);
}


// void    start_dinner(t_table *table)
// {
//     int i;
//     pthread_t monitor_death;
//     long long error_type;

//     table->start_time = current_time();
//     table->instant_time = current_time() - table->start_time;
//     i = -1;
//     odd_picks(&table->philos[0]); //prob is here
//     while(++i < table->philo_nbr)
//     {
//         error_type = pthread_create(&table->philos[i].thread, NULL, routine, &table->philos[i]);
//         if (error_type != 0)
//         {
//             printf("----------enter error----------\n");
//             exit_dinner(table, error_type, i);
//             return;
//         }
//         table->philos[i].last_meal = 0;
//     }
//     error_type = pthread_create(&monitor_death, NULL, monitor_routine, (void *) table);
//     exit_dinner(table, error_type, i);
//     pthread_join(monitor_death, NULL);
//     return;
// }