/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:12:59 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/19 15:44:43 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
    1. fake to lock the fork
    2. sleep until monitor busts it
*/
void    *only_philo(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    wait_all_threads(philo->data);
    printf("LAAA\n");
    set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILISECOND));
    increase_long(&philo->data->data_mutex, &philo->data->threads_running_nbr);
    display_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
    while (simulation_finished(philo->data) == 0)
        usleep(200);
    return (NULL);
}


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
    set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILISECOND));
    philo->meals_nbr++;
    display_status(EATING, philo, DEBUG_MODE);
    precise_usleep(philo->data->time_to_eat, philo->data);
    if (philo->data->nbr_max_meals > 0 
            && philo->meals_nbr == philo->data->nbr_max_meals)
        set_int(&philo->philo_mutex, &philo->full, 1);
    safe_mutex(&philo->first_fork->fork, UNLOCK);
    safe_mutex(&philo->second_fork->fork, UNLOCK);
}

/*
    1. even case --> fair
    2. odd case --> unfair
        --> compute the available time to think
*/
void thinking(t_philo *philo, int pre_simulation)
{
    long    t_eat;
    long    t_sleep;
    long    t_think;
    
    if (pre_simulation == 0)
        display_status(THINKING, philo, DEBUG_MODE);
    if (philo->data->philos_nbr % 2 ==0)
        return;
    t_eat = philo->data->time_to_eat;
    t_sleep = philo->data->time_to_sleep;
    t_think = (t_eat * 2) - t_sleep;
    if (t_think < 0)
        t_think = 0;
    precise_usleep(t_think * 0.42, philo->data);
}

/*
    1. wait for all philos then synchro starts
    2. desynchronize the loop to cutsom the thinking time
        and make the system faire in case of odd nbr of philos
    3. loop:
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
    set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILISECOND));
    increase_long(&philo->data->data_mutex, &philo->data->threads_running_nbr);
    desynchronize_philos(philo);
    while (simulation_finished(philo->data) == 0)
    {
        if (philo->full == 1)
            break;
        eat(philo);
        display_status(SLEEPING, philo, DEBUG_MODE);
        precise_usleep(philo->data->time_to_sleep, philo->data);
        thinking(philo, 0);
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
    if (!data)
        printf("No data dinner start function\n");
    if (data->nbr_max_meals == 0)
        return;
    if (data->philos_nbr < 1)
        printf("No philos[0]\n");
    else if (data->philos_nbr == 1)
    {
        printf("111111\n");
        safe_threads(&data->philos[0].thread_id, only_philo, &data->philos[0], CREATE);
    }
    else
    {
        printf(">>>>> 1\n");
        while (i < data->philos_nbr)
        {
            safe_threads(&data->philos[i].thread_id, dinner_simulation, 
                    &data->philos[i], CREATE);
            i++;
        }
    }
    safe_threads(&data->monitor, monitor_dinner(data), data, CREATE);
    data->start_t = gettime(MILISECOND);
    set_int(&data->data_mutex, &data->all_threads_ready, 1);
    i = 0;
    while (i < data->philos_nbr)
    {
        safe_threads(&data->philos[i].thread_id, NULL, NULL, JOIN);
        i++;
    }
    set_int(&data->data_mutex, &data->end, 1);
    safe_threads(&data->monitor, NULL, NULL, JOIN);
}