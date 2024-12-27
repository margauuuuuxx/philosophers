/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 11:26:27 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/27 12:37:50 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
./philo <nbr of philos> <t die> <t eat> <t sleep> <max meals>

Define a philosopher as a thread
Define the fork as the mutex that manage the different threads
*/

int main(int argc, char **argv)
{
    t_data  data;
    
    if (argc == 5 || argc == 6)
    {
        parse_input(&data, argv); // --> OK
        data_init(&data); // --> OK
        threading(&data);
        clean(&data);
    }
    else
    {
         error_exit("Wrong input, please enter this:\n \
                \t ./philo <nbr of philos> <t die> <t eat> <t sleep> (<max meals>)");   
    }
}