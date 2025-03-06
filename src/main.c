/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:11:07 by stephen           #+#    #+#             */
/*   Updated: 2025/03/06 14:46:28 by scesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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
