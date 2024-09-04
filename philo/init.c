/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 21:04:00 by marlonco          #+#    #+#             */
/*   Updated: 2024/09/04 12:24:47 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


/*
    even / odd assignment
    
    right fork  = philo_id - 1 = position i
        --> since the array begins at 0 but the nbr of philos begins at 1
    left fork   = (philo relative position (starting from 0) + 1) % philo nbr
                = philo_id % philo nbr
*/
static void assign_forks(t_philo *philo, t_fork *forks, int i)
{
    int philo_nbr;

    philo_nbr = philo->data->philos_nbr;
    if (philo->id % 2 == 0)
    {
        philo->first_fork = &forks[i];
        philo->second_fork = &forks[philo->id % philo_nbr];
    }
    else
    {
        philo->first_fork = &forks[philo->id % philo_nbr];
        philo->second_fork = &forks[i];
    }
}

static void philo_init(t_data *data)
{
    int i;
    t_philo *philo;

    i = 0;
    while (i < data->philos_nbr)
    {
        philo = data->philos + i;
        philo->id = i + 1;
        philo->full = -1;
        philo->meals_nbr = 0;
        philo->data = data;
        assign_forks(philo, data->forks, i);
        i++;
    }
}

void    data_init(t_data *data)
{
    int i;

    i = 0;
    data->end = 0;
    data->all_threads_ready = 0;
    data->philos = safe_malloc(data->philos_nbr * sizeof(t_philo));
    safe_mutex(data->data_mutex, INIT);
    data->forks = safe_malloc(data->philos_nbr * sizeof(t_fork));
    while (i < data->philos_nbr)
    {
        safe_mutex(&data->forks[i].fork, INIT);
        data->forks[i].fork_id = i;
        i++;
    }
    philo_init(data);
}