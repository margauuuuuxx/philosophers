/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 12:45:18 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/30 14:54:32 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_sleep(t_data *data, int t)
{
	int	start;

	start = gettime(data);
	while (gettime(data) < start + t)
		usleep(100);
}

void	display(t_data *data, int i, int code)
{
	safe_mutex(&data->print_mutex, LOCK);
	if (code == FORK && !has_died(data))
		printf("%-6ld %d has taken a fork\n", gettime(data),
			data->philos[i].id);
	else if (code == EATING && !has_died(data))
		printf("%-6ld %d is eating\n", gettime(data), data->philos[i].id);
	else if (code == SLEEPING && !has_died(data))
		printf("%-6ld %d is sleeping\n", gettime(data), data->philos[i].id);
	else if (code == THINKING && !has_died(data))
		printf("%-6ld %d is thinking\n", gettime(data), data->philos[i].id);
	else if (code == DIED && !has_died(data))
	{
		printf("%-6ld %d died\n", gettime(data), data->philos[i].id);
		safe_mutex(&data->data_mutex, LOCK);
		data->philos[i].dead = true;
		safe_mutex(&data->data_mutex, UNLOCK);
	}
	safe_mutex(&data->print_mutex, UNLOCK);
}

void	takefork(t_data *data, int i1, int i2)
{
	safe_mutex(&data->philos[i1].fork, LOCK);
	display(data, i1, FORK);
	safe_mutex(&data->philos[i2].fork, LOCK);
	display(data, i1, FORK);
}

void	eat(t_data *data, int i1, int i2)
{
	display(data, i1, EATING);
	safe_mutex(&data->eat_mutex, LOCK);
	data->philos[i1].last_meal_time = gettime(data);
	data->philos[i1].meals_nbr += 1;
	safe_mutex(&data->eat_mutex, UNLOCK);
	ft_sleep(data, data->time_to_eat);
	safe_mutex(&data->philos[i2].fork, UNLOCK);
	safe_mutex(&data->philos[i1].fork, UNLOCK);
}

void	sleeping(t_data *data, int i)
{
	display(data, i, SLEEPING);
	ft_sleep(data, data->time_to_sleep);
}
