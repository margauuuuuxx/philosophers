/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 21:04:00 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/30 15:04:02 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	philo_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_nbr)
	{
		data->philos[i].id = i + 1;
		data->philos[i].full = false;
		data->philos[i].dead = false;
		data->philos[i].meals_nbr = 0;
		data->philos->last_meal_time = 0;
		safe_mutex(&data->philos[i].fork, INIT);
		safe_mutex(&data->philos[i].last_meal_time_mutex, INIT);
		i++;
	}
}

void	data_init(t_data *data)
{
	data->philos = safe_malloc(data->philos_nbr * sizeof(t_philo));
	data->start_t = 0;
	safe_mutex(&data->data_mutex, INIT);
	safe_mutex(&data->print_mutex, INIT);
	safe_mutex(&data->eat_mutex, INIT);
	safe_mutex(&data->time_mutex, INIT);
	philo_init(data);
}
