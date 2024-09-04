/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 11:26:31 by marlonco          #+#    #+#             */
/*   Updated: 2024/09/04 13:08:36 by marlonco         ###   ########.fr       */
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
#include <errno.h>

typedef pthread_mutex_t t_mutex;

struct  s_data;

typedef struct s_data   t_data;
typedef struct s_philo  t_philo;


typedef struct s_fork
{
    t_mutex fork;
    int     fork_id;
    
}   t_fork;

struct s_philo
 {
    int         id;
    long        meals_nbr;
    int         full; // if meals_nbr == max_number of meals 
    long        last_meal_time;
    t_fork      *first_fork;
    t_fork      *second_fork;
    pthread_t   thread_id;
    t_data      *data;
 };
 
struct s_data
{
    long    philos_nbr;
    long    time_to_die;
    long    time_to_eat;
    long    time_to_sleep;
    long    nbr_max_meals;
    long    start_t;
    int     end;
    int     all_threads_ready;
    t_mutex data_mutex;
    t_fork  *forks;
    t_philo *philos;
};

// codes for mutex & thread fcts
typedef enum e_opcode
{
    LOCK,
    UNLOCK,
    INIT,
    DESTROY,
    CREATE,
    JOIN,
    DETACH,
}   t_opcode;

// codes for gettime
typedef enum e_time_code
{
    SECOND,
    MILISECOND,
    MICROSECOND,
}   t_time_code;

// parsing
void    parse_input(t_data *data, char **argv);

// utils
void    error_exit(const char *error);
long    atol(const char *str);

#endif