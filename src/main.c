/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephen <stephen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:11:07 by stephen           #+#    #+#             */
/*   Updated: 2025/03/03 17:30:48 by stephen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// add error messages
void    init_table(int ac, char **av, t_table *table)
{
    int nbr;

    table->philo_nbr = ft_atoi(av[1]);
    table->ttd = ft_atoi(av[2]);
    table->tte = ft_atoi(av[3]);
    table->tts = ft_atoi(av[4]);
    table->philos = malloc(sizeof(t_philosopher) * table->philo_nbr);
    table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_nbr);
    if (!table->philos || !table->forks)
        exit(MALLOC_FAILURE);
    nbr = -1;
    while (++nbr < table->philo_nbr)
    {
        if (pthread_mutex_init(&table->forks[nbr], NULL) != 0)
            exit(EXIT_FAILURE);
    }
    nbr = -1;
    while (++nbr < table->philo_nbr)
    {
        if(ac == 6)
            table->philos[nbr].times_left_to_eat = ft_atoi(av[5]);
        else
            table->time_must_eat = NOT_MENTIONNED;
        table->philos[nbr].number = nbr + 1;
        table->philos[nbr].table = table;
        table->philos[nbr].l_fork = &table->forks[nbr];
        table->philos[nbr].r_fork = &table->forks[(nbr + 1) % table->philo_nbr]; //philo_nbr is for the last philo to get the right r_fork
        pthread_mutex_init(&table->death_mutex, NULL);
        table->smn_died = 0;
    }
    return;
}

int main(int ac, char **av)
{
    t_table table;
    int i;

    if(ac != 5 && ac != 6)
    {
        ft_putchar_fd("Wrong arguments number\n", 1);
        return(1);          //exit message needed ?
    }
    i = 1;
    while(i < ac)
    {
        if(!valid_number(av[i]))
        {
            ft_putchar_fd("Wrong arguments\n", 1);
            return(1);  //exit message needed ?
        }
        i++;
    }
    init_table(ac, av, &table);
    start_dinner(&table);
    return(0);
}
