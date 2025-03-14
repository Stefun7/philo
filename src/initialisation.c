/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:33:51 by scesar            #+#    #+#             */
/*   Updated: 2025/03/14 16:53:57 by scesar           ###   ########.fr       */
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
        if(ac == 6)
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
    table->philo_nbr = my_atoi(av[1]);
    table->ttd = my_atoi(av[2]);
    table->tte = my_atoi(av[3]);
    table->tts = my_atoi(av[4]);
    if (ac == 6)
        table->time_must_eat = my_atoi(av[5]);
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
    // printf("philo nbr : %d \nttd : %d \ntte : %d \ntts : %d \n tme : %d\n",
    // table->philo_nbr, table->ttd, table->tte, table->tts, table->time_must_eat);
}

void    init_dinner(int ac, char **av, t_table *table)
{
    init_table(ac, av, table);
    init_philos(ac, table);
}

//make thread_fail fct and maybe change start_dinner to return non void 

void    start_dinner(t_table *table)
{
    int i;
    pthread_t monitor_death;
    long long error_type;

    table->start_time = current_time();
    table->instant_time = current_time() - table->start_time;
    i = -1;
    odd_picks(&table->philos[0]); //prob is here
    while(++i < table->philo_nbr)
    {
        error_type = pthread_create(&table->philos[i].thread, NULL, routine, &table->philos[i]);
        if (error_type != 0)
            thread_failure(table, error_type);
          //  exit(THREAD_CREATION_FAILURE);
        table->philos[i].last_meal = 0;
    }
    error_type = pthread_create(&monitor_death, NULL, monitor_routine, (void *) table);
        if (error_type != 0)
            thread_failure(table, error_type);
        // exit(THREAD_CREATION_FAILURE);//can't exit
    i = -1;
    while(++i < table->philo_nbr)
        pthread_join(table->philos[i].thread, NULL);//can't exit
    pthread_join(monitor_death, NULL);
    free(table->philos);
    free(table->forks);
    return;
}
