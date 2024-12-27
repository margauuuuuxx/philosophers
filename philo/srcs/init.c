/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 21:04:00 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/27 12:37:04 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void philo_init(t_data *data) // OK
{
    int i;

    i = 0;
    while (i < data->philos_nbr) // OK
    {
        data->philos[i].id = i + 1;
        data->philos[i].full = false;
        data->philos[i].dead = false;
        data->philos[i].meals_nbr = 0;
        data->philos->last_meal_time = 0;
        safe_mutex(&data->philos[i].fork, INIT);
        i++;
    }
}

void    data_init(t_data *data)
{
    data->philos = safe_malloc(data->philos_nbr * sizeof(t_philo));
    data->start_t = 0;
    safe_mutex(&data->data_mutex, INIT);
    safe_mutex(&data->print_mutex, INIT);
    safe_mutex(&data->eat_mutex, INIT);
    safe_mutex(&data->time_mutex, INIT);
    philo_init(data);
    
    printf("\n**************\n\n");
    printf("after data_init:\ndata:\n\tstart_t = %ld\n", data->start_t);
    int i = 0;
    printf("philos:\n");
    while (i < data->philos_nbr)
    {
        printf("\ti iterator in print statement: %d\n", i);
        printf("\tid = %d\tmeals_nbr = %ld\tfull: %d\tlast meal time = %ld\tdead: %d\n", data->philos[i].id, data->philos[i].meals_nbr, data->philos[i].full, data->philos[i].last_meal_time, data->philos[i].dead);
        i++;
    }
    printf("END\n");
}