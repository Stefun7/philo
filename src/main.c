/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:11:07 by stephen           #+#    #+#             */
/*   Updated: 2025/03/05 18:49:00 by scesar           ###   ########.fr       */
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
            table->philos[nbr].times_left_to_eat = table->time_must_eat;
        table->philos[nbr].state = ALIVE;
        table->philos[nbr].number = nbr + 1;
        table->philos[nbr].table = table;
        table->philos[nbr].l_fork = &table->forks[nbr];
        table->philos[nbr].r_fork = &table->forks[(nbr + 1) % table->philo_nbr]; //philo_nbr is for the last philo to get the right r_fork
    }
}

void    init_table(int ac, char **av, t_table *table)
{
    table->philo_nbr = ft_atoi(av[1]);
    table->ttd = ft_atoi(av[2]);
    table->tte = ft_atoi(av[3]);
    table->tts = ft_atoi(av[4]);
    if (ac == 6)
        table->time_must_eat = ft_atoi(av[5]);
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
    // table->start_time = current_time();
}

void    init_dinner(int ac, char **av, t_table *table)
{

    init_table(ac, av, table);
    init_philos(ac, table);
    
    return;
}

int main(int ac, char **av)
{
    t_table table;
    int i;

    if(ac != 5 && ac != 6)
    {
        printf("Wrong arguments number\n");
        return(1);          //exit message needed ?
    }
    i = 1;
    while(i < ac)
    {
        if(!valid_number(av[i]))
        {
            printf("Argument number %d not correct \n", i);
            return(1);  //exit message needed ?
        }
        i++;
    }
    init_dinner(ac, av, &table);
    start_dinner(&table);
    return(0);
}
