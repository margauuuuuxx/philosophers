/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 21:04:00 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/19 15:57:06 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


/*
    even / odd assignment
    
    right fork  = philo_id - 1 = position i
        --> since the array begins at 0 but the nbr of philos begins at 1
    left fork   = (philo relative position (starting from 0) + 1) % philo nbr
                = philo_id % philo nbr
*/

static void assign_forks(t_philo *philo, t_fork *forks, int i) // OK
{
    int philo_nbr;

    philo_nbr = philo->data->philos_nbr;
    printf("philo nbr dans assign fork: %d\n", philo_nbr);
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
    //printf("Philo id: %d\n1st fork: %d\n2nd fork: %d\n\n", philo->id, philo->first_fork->fork_id, philo->second_fork->fork_id);
}

static void philo_init(t_data *data) // OK
{
    int i;
    t_philo *philo;

    i = 0;
    while (i < data->philos_nbr) // OK
    {
        //philo = data->philos + i;
        data->philos[i].id = i + 1;
        data->philos[i].full = false;
        data->philos[i].dead = false;
        data->philos[i].meals_nbr = 0;
        //data->philos[i].data = data;
        safe_mutex(&data->philos[i].fork, INIT);
        // assign_forks(philo, data->forks, i);
        i++;
    }
}

void    data_init(t_data *data)
{
    // int i;

    // i = 0;
    // data->end = 0;
    // data->all_threads_ready = 0;
    // data->threads_running_nbr = 0;
    data->philos = safe_malloc(data->philos_nbr * sizeof(t_philo));
    data->start_t = 0;
    safe_mutex(&data->data_mutex, INIT);
    safe_mutex(&data->print_mutex, INIT);
    safe_mutex(&data->eat_mutex, INIT);
    safe_mutex(&data->time_mutex, INIT);
    // data->forks = safe_malloc(data->philos_nbr * sizeof(t_fork));
    // while (i < data->philos_nbr) // -->OK
    // {
    //     safe_mutex(&data->forks[i].fork, INIT);
    //     data->forks[i].fork_id = i;
    //     i++;
    // }
    philo_init(data);
}