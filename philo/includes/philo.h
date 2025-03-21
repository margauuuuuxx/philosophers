/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 11:26:31 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/30 16:44:38 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef pthread_mutex_t	t_mutex;

typedef struct s_philo
{
	int					id;
	long				meals_nbr;
	bool				full;
	long				last_meal_time;
	bool				dead;
	pthread_t			thread_id;
	t_mutex				fork;
	t_mutex				last_meal_time_mutex;
}						t_philo;

typedef struct s_data
{
	long				philos_nbr;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				nbr_max_meals;
	long				start_t;
	pthread_t			monitor;
	t_mutex				data_mutex;
	t_mutex				print_mutex;
	t_mutex				eat_mutex;
	t_mutex				time_mutex;
	t_philo				*philos;
}						t_data;

typedef struct s_all
{
	t_data				*data;
	unsigned int		index;
}						t_all;

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}						t_opcode;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	FORK,
	DIED,
}						t_philo_status;

//      ##  FUNCTONS    ##
// actions
void					ft_sleep(t_data *data, int t);
void					display(t_data *data, int i, int code);
void					takefork(t_data *data, int i1, int i2);
void					eat(t_data *data, int i1, int i2);
void					sleeping(t_data *data, int i);
// init
void					data_init(t_data *data);
// parsing
void					parse_input(t_data *data, char **argv);
// routine
int						threading(t_data *data);
// safe
void					*safe_malloc(size_t bytes);
void					*safe_mutex(t_mutex *mutex, t_opcode opcode);
void					safe_threads(pthread_t *thread, void *(*foo)(void *),
							void *data, t_opcode opcode);
// utils
void					error_exit(const char *error);
long					gettime(t_data *data);
void					clean(t_data *data);
t_all					*all_infos(t_data *data);
bool					has_died(t_data *data);
// utils2
void					ft_putchar_fd(char c, int fd);
int						left_index(t_data *data, int i);
bool					eaten_enough(t_data *data);
long					time_since_last(t_data *data, int i);
int						letter_check(char **argv);

#endif