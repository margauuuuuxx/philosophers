/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:13:27 by marlonco          #+#    #+#             */
/*   Updated: 2024/09/12 15:12:36 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    error_exit(const char *error)
{
    printf("%s\n", error);
    exit(EXIT_FAILURE);
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
        return(tv.tv_sec + (tv.tv_usec / 1e6));
    else if (time_code == MILISECOND)
        return((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
    else if (time_code == MICROSECOND)
        return((tv.tv_sec * 1e6) + tv.tv_sec);
    else
        error_exit("Wrong input to gettimeofday");
    return (505);
}

/*
    #   PRECISE USLEEP  #
    1. usleep the majority of the time --> not CPU intensive
    2. refine last ms with spinlock
*/
void    precise_usleep(long usec, t_data *data)
{
    long    start;
    long    elapsed;
    long    remaining;

    start = gettime(MICROSECOND);
    while ((gettime(MICROSECOND) - start) < usec)
    {
        if (simulation_finished(data) == 1)
            break;
        elapsed = gettime(MICROSECOND) - start;
        remaining = usec - elapsed;
        if (remaining > 1e3)
            usleep(remaining / 2);
        else
        {
            while ((gettime(MICROSECOND) - start) < usec)
                ;
        }
    }
}

void clean  (t_data *data)
{
    t_philo *philo;
    int     i;
    
    i = 0;
    while (i < data->philos_nbr)
    {
        philo = data->philos + i;
        safe_mutex(&philo->philo_mutex, DESTROY);
        i++;
    }
    safe_mutex(&data->data_mutex, DESTROY);
    safe_mutex(&data->write_lock, DESTROY);
    free(data->forks);
    free(&data->philos);
}