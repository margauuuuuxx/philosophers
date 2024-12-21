/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:22:09 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/19 15:44:49 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
    <time in ms> <philo_id> <action>
*/

static void display_status_debug(t_philo_status status, t_philo *philo, long elapsed)
{
    (void) elapsed;
    if (status == TAKE_FIRST_FORK && simulation_finished(philo->data) == 0)
        printf("%-6ld %d has taken its 1st fork\n\tfork id: %d", elapsed, philo->id, philo->first_fork->fork_id);
    if (status == TAKE_SECOND_FORK && simulation_finished(philo->data) == 0)
        printf("%-6ld %d has taken its second fork\n\t fork id: %d", elapsed, philo->id, philo->second_fork->fork_id);
    else if (status == EATING && simulation_finished(philo->data) == 0)
        printf("%-6ld %d is eating\n\tnumber of meals eaten by %d: %ld", elapsed, philo->id, philo->id, philo->meals_nbr);
    else if (status == SLEEPING && simulation_finished(philo->data) == 0)
        printf("%-6ld %d is sleeping\n", elapsed, philo->id);
    else if (status == THINKING && simulation_finished(philo->data) == 0)
        printf("%-6ld %d is thinking\n", elapsed, philo->id);
    else if (status == DIED)
        printf("%-6ld %d died\n", elapsed, philo->id); 
}

void    display_status(t_philo_status status, t_philo *philo, int debug)
{
    long    elapsed;

    elapsed = gettime(MILISECOND);
    if (philo->full == 1)
        return;
    safe_mutex(&philo->data->write_lock, LOCK);
    if (debug == 1)
        display_status_debug(status, philo, elapsed);
    else 
    {
        if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
                && simulation_finished(philo->data) == 0)
            printf("%-6ld %d has taken a fork\n", elapsed, philo->id);
        else if (status == EATING && simulation_finished(philo->data) == 0)
            printf("%-6ld %d is eating\n", elapsed, philo->id);
        else if (status == SLEEPING && simulation_finished(philo->data) == 0)
            printf("%-6ld %d is sleeping\n", elapsed, philo->id);
        else if (status == THINKING && simulation_finished(philo->data) == 0)
            printf("%-6ld %d is thinking\n", elapsed, philo->id);
        else if (status == DIED)
            printf("%-6ld %d died\n", elapsed, philo->id); 
    }
    safe_mutex(&philo->data->write_lock, UNLOCK);
}