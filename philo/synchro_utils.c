/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:57:26 by marlonco          #+#    #+#             */
/*   Updated: 2024/09/04 13:03:11 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
    # SPINLOCK #
    continuous check (spin) in a loop until the resource that 
    was used by another thread becomes available again
*/
void    wait_all_threads(t_data *data)
{
    while (get_int(&data->data_mutex, data->all_threads_ready) == 0)
        ;
}