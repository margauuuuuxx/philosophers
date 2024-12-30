/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:48:39 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/30 14:47:50 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	left_index(t_data *data, int i)
{
	if (i == 0)
		return (data->philos_nbr - 1);
	return (i - 1);
}

static bool	eaten_enough(t_data *data)
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

static void	only_philo(t_data *data, int i)
{
	display(data, i, FORK);
	ft_sleep(data, data->time_to_die);
	display(data, i, DIED);
}

static void	*routine(void *args)
{
	t_all	*all;
	t_data	*data;
	int		i1;
	int		i2;

	all = (t_all *)args;
	i1 = all->index;
	data = all->data;
	i2 = left_index(data, i1);
	safe_mutex(&data->philos[i1].last_meal_time_mutex, LOCK);
	data->philos[i1].last_meal_time = gettime(data);
	safe_mutex(&data->philos[i1].last_meal_time_mutex, UNLOCK);
	if (data->philos[i1].id % 2 == 0)
		ft_sleep(data, data->time_to_eat / 10);
	while (!has_died(data))
	{
		if (data->philos_nbr == 1)
			only_philo(data, i1);
		else
		{
			takefork(data, i1, i2);
			eat(data, i1, i2);
			if (data->philos[i1].meals_nbr == data->nbr_max_meals)
				return (NULL);
			sleeping(data, i1);
			display(data, i1, THINKING);
		}
	}
	return (NULL);
}

static long	time_since_last(t_data *data, int i)
{
	long	now;
	long	time_since_last;

	now = gettime(data);
	safe_mutex(&data->philos[i].last_meal_time_mutex, LOCK);
	time_since_last = now - data->philos[i].last_meal_time;
	safe_mutex(&data->philos[i].last_meal_time_mutex, UNLOCK);
	return (time_since_last);
}

static void	*ft_monitor(void *args)
{
	t_data	*data;
	int		i;

	data = (t_data *)args;
	while (1)
	{
		i = 0;
		while (i < data->philos_nbr)
		{
			safe_mutex(&data->eat_mutex, LOCK);
			if (time_since_last(data, i) >= data->time_to_die)
			{
				display(data, i, DIED);
				return (safe_mutex(&data->eat_mutex, UNLOCK), NULL);
			}
			safe_mutex(&data->eat_mutex, UNLOCK);
			if (eaten_enough(data))
				return (NULL);
			i++;
		}
	}
	return (NULL);
}

int	threading(t_data *data)
{
	t_all	*all;
	int		i;

	all = all_infos(data);
	if (!all)
		return (1);
	i = 0;
	while (i < data->philos_nbr)
	{
		if (i % 2 != 0)
			usleep(data->time_to_die / 8);
		safe_threads(&data->philos[i].thread_id, &routine, &all[i], CREATE);
		i++;
	}
	safe_threads(&data->monitor, &ft_monitor, data, CREATE);
	i = 0;
	while (i < data->philos_nbr)
	{
		safe_threads(&data->philos[i].thread_id, NULL, NULL, JOIN);
		i++;
	}
	safe_threads(&data->monitor, NULL, NULL, JOIN);
	return (free(all), 0);
}
