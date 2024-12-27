/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:13:27 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/27 13:26:32 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void    error_exit(const char *error)
{
    // DONT FORGET TO FREE BEFORE EXITING 
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
    unsing long var type because milliseconds can quickly exceed 
    the max 32-bits int
*/
long    gettime(t_data *data) // time in MILISECONDS by default 
{
    struct timeval  tv;
    struct timeval  start;
    long            result;

    safe_mutex(&data->time_mutex, LOCK);
    if (!data->start_t)
    {
        if (gettimeofday(&start, NULL) == -1)
            error_exit("Function gettimeofday failed.");
        data->start_t = start.tv_sec * 1e3 + start.tv_usec / 1e3;
    }
    if (gettimeofday(&tv, NULL) == -1)
        error_exit("Function gettimeofday failed.");
    result = (tv.tv_sec * 1e3) + (tv.tv_usec / 1e3) - data->start_t;
    safe_mutex(&data->time_mutex, UNLOCK);
    return (result);
}

/*
    #   PRECISE USLEEP  #
    1. usleep the majority of the time --> not CPU intensive
    2. refine last ms with spinlock
*/
// void    precise_usleep(long usec, t_data *data)
// {
//     long    start;
//     long    elapsed;
//     long    remaining;

//     start = gettime(MICROSECOND);
//     while ((gettime(MICROSECOND) - start) < usec)
//     {
//         if (simulation_finished(data) == 1)
//             break;
//         elapsed = gettime(MICROSECOND) - start;
//         remaining = usec - elapsed;
//         if (remaining > 1e3)
//             usleep(remaining / 2);
//         else
//         {
//             while ((gettime(MICROSECOND) - start) < usec)
//                 ;
//         }
//     }
// }

void clean  (t_data *data)
{
    int i;
    
    safe_mutex(&data->print_mutex, DESTROY);
    safe_mutex(&data->data_mutex, DESTROY);
    i = 0;
    while (i < data->philos_nbr)
    {
        safe_mutex(&data->philos[i].fork, DESTROY);
        i++;
    }
    free(data->philos);
}

t_all   *all_infos(t_data *data)
{
    t_all   *all;
    int     i;

    all = safe_malloc(data->philos_nbr * sizeof(t_all));
    i = 0;
    while (i < data->philos_nbr)
    {
        all[i].data = data;
        all[i].index = i;
        i++;
    }
    return (all);
}

bool    has_died(t_data *data)
{
    int i;

    i = 0;
    safe_mutex(&data->data_mutex, LOCK);
    while (i < data->philos_nbr)
    {
        if (data->philos[i].dead == true)
            return (safe_mutex(&data->data_mutex, UNLOCK), true);
        i++;
    }
    return (safe_mutex(&data->data_mutex, UNLOCK), false);
}