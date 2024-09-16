/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:55:23 by marlonco          #+#    #+#             */
/*   Updated: 2024/09/16 14:43:47 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
    if t since las meal > t to die --> = 1
*/
static int  philo_died(t_philo *philo)
{
    long    elapsed;
    long    t_to_die;
    
    if (get_int(philo->philo_mutex, &philo->full) == 1)
        return(0);
    elapsed = gettime(MILISECOND) - get_long(philo->philo_mutex, &philo->last_meal_time);
    t_to_die = philo->data->time_to_die / 1e3;
    if (elapsed > t_to_die) // CHECK IF >=
        return (1);
    return (0);
}

/*
    1. make sure all philos are running
        --> if not spinlock
    2. checking continuously if each philo isnt dead 
*/
void    *monitor_dinner(void *input)
{
    t_data  *data;
    int     i;

    data = (t_data *)input;
    while (all_threads_running(&data->data_mutex, &data->threads_running_nbr, data->philos_nbr))
        ;
    while (simulation_finished(data) == 0)
    {
        i = 0;
        while (i < data->philos_nbr && simulation_finished(data) == 0)
        {
            if (philo_died(data->philos + i))
            {
                set_int(&data->data_mutex, &data->end, 1);
                display_status(DIED, data->philos + i, DEBUG_MODE);
            }
            i++;
        }
    }
    return (NULL);
}