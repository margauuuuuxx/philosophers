/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:13:27 by marlonco          #+#    #+#             */
/*   Updated: 2024/09/04 13:14:36 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    error_exit(const char *error)
{
    printf("%s\n", error);
    exit(EXIT_FAILURE);
}

static  const char *valid_input(const char *str)
{
    int len;
    const char *nbr;

    len = 0;
    while ((*str >= 9 && *str <= 13) || *str == 32)
        str++;
    if (*str == '+')
        str++;
    else if (*str == '-')
        error_exit("Invalid input: negative numbers");
    if (!(*str >= '0' && *str <= '9'))
        error_exit("Invalid input: not only numbers provided");
    nbr = str;
    while (*str >= '0' && *str <= '9')
    {
        str++;
        len++;
    }
    if (len > 10)
        error_exit("Invalid input: number(s) too big");
   return (nbr); 
}

long    atol(const char *str)
{
    long    nbr;
    
    nbr = 0;
    str = valid_input(str);
    while (*str >= '0' && *str <= '9')
        nbr = nbr * 10 + (*str++ - '0');
    if (nbr > INT_MAX)
        error_exit("Invalid input: number(s) too big");
    return (nbr);
}

/*
    time code --> sec ms μs
    struct timeval {
        time_t  tv_sec; // SECONDS
        suseconds_t tv_usec; // MICROSECONDS
    }
        --> defined in <sys/time.h> and used in the fct gettimeofday
*/
long    gettime(t_time_code time_code)
{
    struct timeval  tv;

    if (gettimeofday(&tv, NULL))
        error_exit("Function gettimeofday failed.");
    if (time_code == SECOND)
        return(tv.tv_sec);
    if (time_code == MICROSECOND)
        return(tv.tv_usec);
}