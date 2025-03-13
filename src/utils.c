/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:03:55 by stephen           #+#    #+#             */
/*   Updated: 2025/03/13 16:31:19 by scesar           ###   ########.fr       */
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
    if(my_atoi(number) == LLONG_MIN)
    {
        printf("Wrong arg range\n");
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
	long long	i;

	i = 0;
	while(i < time)
	{
		pthread_mutex_lock(&table->death_mutex);
		if(table->smn_died)
		{
			pthread_mutex_unlock(&table->death_mutex);
			return;
		}
		pthread_mutex_unlock(&table->death_mutex);
		usleep(2000);
		i += 2000;
	}
	return;
}

// my_usleep(one_philo->table , (one_philo->table->tte * 1000LL));

// my_usleep(one_philo->table, (one_philo->table->tts * 1000LL));

// my_usleep(one_philo->table, (one_philo->table->tts * 1000LL));