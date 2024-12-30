/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 11:26:27 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/30 14:54:51 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
./philo <nbr of philos> <t die> <t eat> <t sleep> <max meals>

Define a philosopher as a thread
Define the fork as the mutex that manage the different threads
*/

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		parse_input(&data, argv);
		if (data.philos_nbr == 0)
			error_exit("Please submit  nbr of philos > 0 :P");
		data_init(&data);
		threading(&data);
		clean(&data);
	}
	else
	{
		error_exit("Wrong input, please enter this:\n \
                \t ./philo <nbr of philos> <t die> <t eat> \
                 <t sleep> (<max meals>)");
	}
}
