/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:22:38 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/30 16:37:51 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
	TO CHECK:
		1. actual numbers
		2. not > INT MAX
		3. timestamps > 60 ms

*/

static const char	*valid_input(const char *str)
{
	int			len;
	const char	*nbr;

	len = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		error_exit("Invalid input: negative numbers");
	if (!(*str >= '0' && *str <= '9'))
		error_exit("Invalid input: not only numbers provided");
	nbr = str;
	while (*str >= '0' && *str <= '9' && *str != '\0')
	{
		str++;
		len++;
	}
	if (len > 10)
		error_exit("Invalid input: number(s) too big");
	return (nbr);
}

static long	ft_atol(const char *str)
{
	long	nbr;

	nbr = 0;
	str = valid_input(str);
	while (*str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + (*str - '0');
		str++;
	}
	if (nbr > INT_MAX)
		error_exit("Invalid input: number(s) too big");
	return (nbr);
}

static void	print_nb(long n, int fd)
{
	if (n / 10)
	{
		print_nb(n / 10, fd);
		print_nb(n % 10, fd);
	}
	else
		ft_putchar_fd(n + '0', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	nbr;

	nbr = (long)n;
	if (nbr < 0)
	{
		write(fd, "-", 1);
		nbr = -nbr;
	}
	print_nb(nbr, fd);
}

/*
We convert miliseconds in microseconds by doing *1e3
because it's the unit of usleep()

< 6e4: limit min treshold to ensure that the values 
		aren't too small for the program
*/
void	parse_input(t_data *data, char **argv)
{
	if (letter_check(argv))
		error_exit("Incorrect input: non-numeric character detected");
	data->philos_nbr = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (data->time_to_die < 60 || data->time_to_eat < 60
		|| data->time_to_die < 60)
		error_exit("Incorrect input: timestamps inferior to 60ms");
	if (argv[5])
		data->nbr_max_meals = ft_atol(argv[5]);
	else
		data->nbr_max_meals = -1;
}
