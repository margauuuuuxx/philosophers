/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:12:59 by marlonco          #+#    #+#             */
/*   Updated: 2024/09/04 12:23:24 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
    1. wait for all philos then synchro starts
    2. endless loop philo
*/
void    *dinner_simulation(void *stuff)
{
    t_philo *philo;
    
    philo = (t_philo *)stuff;
    wait_all_threads(philo->data);
}

/*
    1. if max meals == 0
    2. if nbr philo == 1
    3. create all threads 
    4. create a monitor thread --> seraching for deaths 
    5. synchronize the beginning of all threads 
    6. join everyone 
*/
void    dinner_start(t_data *data)
{
    int i;

    i = 0;
    if (data->nbr_max_meals == 0)
        return;
    else if (data->philos_nbr == 1)
        //TO DO;
    else
    {
        while (i < data->philos_nbr)
        {
            safe_threads(&data->philos[i].thread_id, dinner_simulation, 
                    &data->philos[i], CREATE);
            i++;
        }
    }
    
}