/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 14:55:32 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/30 15:05:20 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

int	left_index(t_data *data, int i)
{
	if (i == 0)
		return (data->philos_nbr - 1);
	return (i - 1);
}

bool	eaten_enough(t_data *data)
{
	int	i;

	if (data->nbr_max_meals == -1)
		return (false);
	i = 0;
	while (i < data->philos_nbr)
	{
		if (data->philos[i].meals_nbr != data->nbr_max_meals)
			return (false);
		i++;
	}
	safe_mutex(&data->data_mutex, LOCK);
	data->philos[0].dead = true;
	safe_mutex(&data->data_mutex, UNLOCK);
	return (true);
}

long	time_since_last(t_data *data, int i)
{
	long	now;
	long	time_since_last;

	now = gettime(data);
	safe_mutex(&data->philos[i].last_meal_time_mutex, LOCK);
	time_since_last = now - data->philos[i].last_meal_time;
	safe_mutex(&data->philos[i].last_meal_time_mutex, UNLOCK);
	return (time_since_last);
}
