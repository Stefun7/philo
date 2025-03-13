/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:03:55 by stephen           #+#    #+#             */
/*   Updated: 2025/03/13 18:58:46 by scesar           ###   ########.fr       */
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
	// usleep(time);
	long long right_now;

	right_now = current_time();
	// printf("time :%lld\ntime_to_reach : %lld\ntime_to_reach -time : %lld\ncurrent_time : %lld\n", time, to_reach, (to_reach - time), current_time());
	while((current_time() - right_now) < time)
	{
		pthread_mutex_lock(&table->death_mutex);
		if(table->smn_died)
		{
			// printf("----yes----\n");
			pthread_mutex_unlock(&table->death_mutex);
			return;
		}
		pthread_mutex_unlock(&table->death_mutex);
		usleep(150);
	}
	return;
}
// void	my_usleep(t_table *table, long long time)
// {
// 	long long to_reach;

// 	to_reach = current_time() + time;
// 	printf("time :%lld\ntime_to_reach : %lld\ntime_to_reach -time : %lld\ncurrent_time : %lld\n", time, to_reach, (to_reach - time), current_time());
// 	while(current_time() < to_reach)
// 	{
// 		pthread_mutex_lock(&table->death_mutex);
// 		if(table->smn_died)
// 		{
// 			pthread_mutex_unlock(&table->death_mutex);
// 			return;
// 		}
// 		pthread_mutex_unlock(&table->death_mutex);
// 		usleep(100);
// 	}
// 	return;
// }
