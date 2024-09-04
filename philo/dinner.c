/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:12:59 by marlonco          #+#    #+#             */
/*   Updated: 2024/09/04 15:08:14 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
    1. grab the forks
    2. eating:
        - write eating status
        - update last meal
        - update meal counter
        - eventually bool full
    3. release forks 
*/    

static void eat(t_philo *philo)
{
    safe_mutex(&philo->first_fork->fork, LOCK);
    display_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
    safe_mutex(&philo->second_fork->fork, LOCK);
    display_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
    set_long(philo->philo_mutex, &philo->last_meal_time, gettime(MILISECOND));
    philo->meals_nbr++;
    display_status(EATING, philo, DEBUG_MODE);
    precise_usleep(philo->data->time_to_eat, philo->data);
    if (philo->data->nbr_max_meals > 0 
            && philo->meals_nbr == philo->data->nbr_max_meals)
        set_int(philo->philo_mutex, philo->full, 1);
    safe_mutex(&philo->first_fork->fork, UNLOCK);
    safe_mutex(&philo->second_fork->fork, UNLOCK);
}

static void thinking(t_philo *philo, int debug)
{
    display_status(THINKING, philo, DEBUG_MODE);
}

/*
    1. wait for all philos then synchro starts
    2. loop:
        a) is full ?
        b) eat
        c) sleep
        d) think
*/
void    *dinner_simulation(void *stuff)
{
    t_philo *philo;
    
    philo = (t_philo *)stuff;
    wait_all_threads(philo->data);
    while (simulation_finished(philo->data) == 0)
    {
        if (philo->full == 1)
            break;
        eat(philo);
        display_status(SLEEPING, philo, DEBUG_MODE);
        precise_usleep(philo->data->time_to_sleep, philo->data);
        thinking(philo);
    }
    return (NULL);
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
    data->start_t = gettime(MILISECOND);
    set_int(&data->data_mutex, data->all_threads_ready, 1);
    i = 0;
    while (i < data->philos_nbr)
    {
        safe_thread(&data->philos[i].id, NULL, NULL, JOIN);
        i++;
    }
    
}