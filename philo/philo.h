/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 11:26:31 by marlonco          #+#    #+#             */
/*   Updated: 2024/09/16 14:41:15 by marlonco         ###   ########.fr       */
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
#include <stdbool.h>

#define DEBUG_MODE 1 // if debug mode == 1 --> then its on 

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
    t_mutex     philo_mutex;
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
    long    threads_running_nbr;
    int     end;
    int     all_threads_ready;
    pthread_t   monitor;
    t_mutex data_mutex;
    t_mutex write_lock;
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

// codes for philo states
typedef enum e_status
{
    EATING,
    SLEEPING,
    THINKING,
    TAKE_FIRST_FORK,
    TAKE_SECOND_FORK,
    DIED,
}   t_philo_status;


//      ##  FUNCTONS    ##
// dinner
void    thinking(t_philo *philo, int pre_simulation);
void    *dinner_simulation(void *stuff);
void    dinner_start(t_data *data);
// display
void    display_status(t_philo_status status, t_philo *philo, int debug);
//  getters & setters
void    set_int(t_mutex *mutex, int *dest, int value);
int     get_int(t_mutex mutex, int *value);
void    set_long(t_mutex *mutex, long *dest, long value);
long    get_long (t_mutex mutex, long *value);
int     simulation_finished(t_data *data);
// init
void    data_init(t_data *data);
// monitor
void    *monitor_dinner(void *input);
// parsing
void    parse_input(t_data *data, char **argv);
// safe
void    *safe_malloc(size_t bytes);
void    *safe_mutex(t_mutex *mutex, t_opcode opcode);
void    safe_threads(pthread_t *thread, void *(*foo)(void *), void *data, t_opcode opcode);
// synchro utils
void    wait_all_threads(t_data *data);
int     all_threads_running(t_mutex *mutex, long *threads_running, long philo_nbr);
void    increase_long(t_mutex *mutex, long *value);
void    desynchronize_philos(t_philo *philo);
// utils
void    error_exit(const char *error);
long    gettime(t_time_code time_code);
void    precise_usleep(long usec, t_data *data);
void    clean(t_data *data);

#endif