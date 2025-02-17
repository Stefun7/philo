/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephen <stephen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:03:55 by stephen           #+#    #+#             */
/*   Updated: 2025/02/12 11:18:07 by stephen          ###   ########.fr       */
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