/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:03:55 by stephen           #+#    #+#             */
/*   Updated: 2025/03/17 17:01:22 by scesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long long current_time(void)
{
    struct timeval time;
    long long sec_since_1970;
    long long sec_since_last;

   gettimeofday(&time, NULL);
   sec_since_1970 = (long long) (time.tv_sec * 1000LL);
   sec_since_last = (long long) (time.tv_usec / 1000);
   return(sec_since_1970 + sec_since_last);
}

int valid_number(char *number)
{
    int i;

    i = 0;
    if(my_atoi(number) == LLONG_MIN || my_atoi(number) == 0)
    {
        printf("Wrong argument range\n");
        return(0);
    }
    while(number[i])
    {
        if (!ft_isdigit(number[i]))
            return(0);
        i++;
    }
    return(1);
}

long long	my_atoi(const char *str)
{
	size_t	i;
	int		neg;
	long	res;

	i = 0;
	neg = 1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+' )
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57 && res >= 0)
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	res *= neg;
	if (ft_strlen(str) != i || res < INT_MIN || res > INT_MAX || i == 0)
		res = LLONG_MIN;
	return (res);
}

void	my_usleep(t_table *table, long long time)
{
	long long to_reach;

	
	to_reach = table->instant_time + time;
	while(table->instant_time < to_reach)
	{
		if(a_philo_is_dead(table))
			return;
		usleep(100);
	}
	return;
}

int exit_dinner(t_table *table, int error_type, int threads_created)
{
	int i;

	printf("--------------philo_out---------------\n");
	if (error_type != 0)
		printf ("Problem trying to create thread. Error type : %d\n", error_type);
	i = -1;
	while(++ i < threads_created)
		pthread_join(table->philos[i].thread, NULL);
	free(table->forks);
	free(table->philos);
	return(0);
}