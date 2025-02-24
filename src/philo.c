/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephen <stephen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:11:07 by stephen           #+#    #+#             */
/*   Updated: 2025/02/18 17:54:25 by stephen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void    init_table(char **av, t_table *table)
{
    int nbr;

    table->philo_nbr = ft_atoi(av[1]);
    table->ttd = ft_atoi(av[2]);
    table->tte = ft_atoi(av[3]);
    table->tts = ft_atoi(av[4]);
    if(av[5])
        table->time_must_eat = av[5];
    else
        table->time_must_eat = NOT_MENTIOENNED;
    table->philos = malloc(sizeof(t_philosopher) * table->philo_nbr);
    table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_nbr);
    if (!table->philos || !table->forks)
        exit("malloc error"); //not correct, need an int in exit
    nbr = -1;
    while (++nbr < table->philo_nbr)
        pthread_mutex_init(&table->forks[nbr], NULL);
    nbr = -1;
    while (++nbr < table->philo_nbr)
    {
        table->philos[nbr].number = nbr + 1;
        table->philos[nbr].table = table;
        table->philos[nbr].l_fork = &table->forks[nbr];
        table->philos[nbr].r_fork = &table->forks[(nbr + 1) % table->philo_nbr]; //philo_nbr is for the last philo to get the right r_fork
    }
    return;
}

int main(int ac, char **av)
{
    t_table table;
    int i;

    i = 1;
    while(av[i])
    {
        if(!valid_number(av[i]))
            return(1);
        i++;
    }
    if(ac != 5 && ac != 6)
        return(1);          //exit message needed ?
    init_table(av, &table);
    start_dinner(&table);
    return(0);
}