/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:25:14 by scesar            #+#    #+#             */
/*   Updated: 2025/03/25 17:44:20 by scesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int ac, char **av)
{
	t_table	table;
	int		i;

	if (ac != 5 && ac != 6)
	{
		printf("Wrong arguments number\n");
		return (1);
	}
	i = 1;
	while (i < ac)
	{
		if (!valid_number(av[i]))
		{
			printf("Argument number %d is incorrect \n", i);
			return (1);
		}
		i++;
	}
	init_dinner(ac, av, &table);
	if (!start_dinner(&table))
		return (1);
	return (0);
}
