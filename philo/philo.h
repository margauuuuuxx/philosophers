/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 11:26:31 by marlonco          #+#    #+#             */
/*   Updated: 2024/08/31 12:20:39 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <limits.h>

typedef pthread_mutex_t t_mutex;

typedef struct s_data   t_data;

typedef struct s_fork
{
    t_mutex fork;
    int     fork_id;
    
}   t_fork;

typedef struct s_philo
 {
    int         id;
    long        meals_nbr;
    int         full; // if meals_nbr == max_number of meals 
    long        last_meal_time;
    t_fork      *left_fork;
    t_fork      *right_fork;
    pthread_t   thread_id;
    t_data      *data;
 }  t_philo;
 
struct s_data
{
    long    philos_nbr;
    long    time_to_die;
    long    time_to_eat;
    long    time_to_sleep;
    long    nbr_max_meals;
    long    start_t;
    int     end_t;
    t_fork  *forks;
    t_philo *philos;
}   t_data;


#endif