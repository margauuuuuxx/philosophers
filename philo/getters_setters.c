/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:25:28 by marlonco          #+#    #+#             */
/*   Updated: 2024/09/04 12:53:42 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
        # PREVENTING RACE CONDITIONS #
    module containing setters_getters to avoid writing
    LOCK / UNLOCK everywhere
*/

void    set_int(t_mutex *mutex, int *dest, int value)
{
    safe_mutex(mutex, LOCK);
    *dest = value;
    safe_mutex(mutex, UNLOCK);
}

int get_int(t_mutex mutex, int *value)
{
    int res;

    safe_mutex(mutex, LOCK);
    res = *value;
    safe_mutex(mutex, UNLOCK);
    return (res);
}

long    set_long(t_mutex *mutex, long *dest, long value)
{
    safe_mutex(mutex, LOCK);
    *dest = value;
    safe_mutex(mutex, UNLOCK);
}

long    get_long(t_mutex mutex, long *value)
{
    long    res;

    safe_mutex(mutex, LOCK);
    res = *value;
    safe_mutex(mutex, UNLOCK);
    return (res);
}

int simulation_finished(t_data *data)
{
    return(get_int(data->data_mutex, &data->end));
}