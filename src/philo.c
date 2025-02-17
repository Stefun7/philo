/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephen <stephen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:11:07 by stephen           #+#    #+#             */
/*   Updated: 2025/02/11 17:41:33 by stephen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void    init_table(char **av, t_table *table)
{
    //don't forget to verify the args (like what happens if they're are < 0)
    int nbr;

    table->philo_nbr = av[1];
    table->ttd = av[2];
    table->tte = av[3];
    table->tts = av[4];
    if(av[5])
        table->time_must_eat = av[5];
    else
        table->time_must_eat = -1;
    table->philos = malloc(sizeof(t_philosopher) * table->philo_nbr);
    table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_nbr);
    if (!table->philos || !table->forks)
        exit("malloc error");
    nbr = -1;
    while (++nbr < table->philo_nbr)
        pthread_mutex_init(&table->forks[nbr], NULL);
    nbr = -1;
    while (++nbr < table->philo_nbr)
    {
        table->philos->number = nbr + 1;
        table->philos->l_fork = &table->forks[nbr];
        table->philos->r_fork = &table->forks[(nbr + 1) % table->philo_nbr]; //philo_nbr is for the last philo to get the right r_fork
    }
    return;
}

int main(int ac, char **av)
{
    t_table table;
    int i;

    i = 0;
    while(av[i])
    {
        if(!ft_isdigit(av[i]))
            return(1);
        i++;
    }
    if(ac != 5 && ac != 6)
        return(1);
    init_table(av, &table);
    start_dinner(&table);
    return(0);
}