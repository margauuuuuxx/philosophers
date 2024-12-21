/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:57:26 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/19 15:45:16 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/*
    # SPINLOCK #
    continuous check (spin) in a loop until the resource that 
    was used by another thread becomes available again
*/
void    wait_all_threads(t_data *data)
{
    while (get_int(data->data_mutex, &data->all_threads_ready) == 0)
        ;
}

/*
    monitor waits until all threads are running
*/
int all_threads_running(t_mutex *mutex, long *threads_running, long philo_nbr)
{
    int result;

    result = 0;
    safe_mutex(mutex, LOCK);
    if (*threads_running == philo_nbr)
        result = 1;
    safe_mutex(mutex, UNLOCK);
    return(result);
}

void    increase_long(t_mutex *mutex, long *value)
{
    safe_mutex(mutex, LOCK);
    (*value)++;
    safe_mutex(mutex, UNLOCK);
}

/*
    Make the system fair
*/
void    desynchronize_philos(t_philo *philo)
{
    if (philo->data->philos_nbr % 2 == 0)
    {
        if (philo->id % 2 == 0)
            precise_usleep(3e4, philo->data);
    }
    else
    {
        if (philo->id % 2)
            thinking(philo, 1);
    }
}