/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephen <stephen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:03:55 by stephen           #+#    #+#             */
/*   Updated: 2025/02/18 17:49:58 by stephen          ###   ########.fr       */
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
    while(number[i])
    {
        if (!ft_isdigit(number[i]))
            return(0);
        i++;
    }
    return(1);
}