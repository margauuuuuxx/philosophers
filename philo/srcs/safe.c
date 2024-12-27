/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlonco <marlonco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 21:38:40 by marlonco          #+#    #+#             */
/*   Updated: 2024/12/27 16:49:14 by marlonco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*safe_malloc(size_t bytes)
{
	void	*result;

	result = malloc(bytes);
	if (result == NULL)
		error_exit("Malloc failure");
	return (result);
}

/*
	status = return value from mutex operatiom
	opcode = operation attempted

		# standard error codes #
	EINVAL  = invalid arg
	EDEADLK = deadlock detected
		--> a deadlock occurs when 2+ threads are waiting for
			each other to release locks, but none of them can proceed
			because each one holds a lock the others need
	EPERM   = attempt to perform a mutex operations
				without the necessary permissions
		--> when a thread that didn't lock a mutex tries to unlock it
	ENOMEM  = unable to allocate the necessary memory
	EBUSY   = resource (mutex/synchronization primitive) is already
				in use/locked --> resource unavailable

	all mutex operations return 0 if correct
	all the error strings come from the man of the fcts
*/
static void	handle_mutex_errors(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (opcode == LOCK || opcode == UNLOCK))
		error_exit("The value specified by mutex is invalid.");
	else if (status == EINVAL && opcode == INIT)
		error_exit("The value specified by attr is invalid.");
	else if (status == EDEADLK)
		error_exit("A deadlock would occur if the \
            thread blocked waiting for mutex.");
	else if (status == EPERM)
		error_exit("The current thread does not hold a lock on mutex");
	else if (status == ENOMEM)
		error_exit("The process connot allocate enough \
            memory to create another mutex.");
	else if (status == EBUSY)
		error_exit("Mutex is locked");
}

void	*safe_mutex(t_mutex *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		handle_mutex_errors(pthread_mutex_lock(mutex), opcode);
	else if (opcode == UNLOCK)
		handle_mutex_errors(pthread_mutex_unlock(mutex), opcode);
	else if (opcode == INIT)
		handle_mutex_errors(pthread_mutex_init(mutex, NULL), opcode);
	else if (opcode == DESTROY)
		handle_mutex_errors(pthread_mutex_destroy(mutex), opcode);
	else
		error_exit("Wrong opcode for mutex handle");
	return (NULL);
}

/*
	EAGAIN  = system resource is temporarily unavailable
	ESRCH   = no such process --> thread doesn't exist
*/

static void	handle_thread_errors(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		error_exit("No resources to create another thread");
	else if (status == EPERM)
		error_exit("The caller does not have appropriate permission\n");
	else if (status == EINVAL && opcode == CREATE)
		error_exit("The value specified by attr is invalid.");
	else if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
		error_exit("The  value specified by thread is not joinable\n");
	else if (status == ESRCH)
		error_exit("No thread could be found corresponding to that \
                    specified by the given thread ID, thread.");
	else if (status == EDEADLK)
		error_exit("A deadlock was detected or the value of \
                    thread specifies teh calling thread.");
	else
		error_exit("Unknown thread error.");
}

void	safe_threads(pthread_t *thread, void *(*foo)(void *), void *data,
		t_opcode opcode)
{
	// HAVE TO FREE WHEN THREADS FAILS
	if (thread == NULL)
	{
		printf("THREADDD\n");
		printf("Null thread safe thread function\n");
		return ;
	}
	if (data == NULL && opcode != JOIN)
	{
		printf("DATAAA\n");
		printf("Null data safe thread function\n");
		return ;
	}
	if (!opcode)
	{
		printf("OPCODEEE\n");
		printf("Null opcode safe thread function\n");
		return ;
	}
	if (opcode == CREATE)
		handle_thread_errors(pthread_create(thread, NULL, foo, data), opcode);
	else if (opcode == JOIN)
		handle_thread_errors(pthread_join(*thread, NULL), opcode);
	else if (opcode == DETACH)
		handle_thread_errors(pthread_detach(*thread), opcode);
	else
		error_exit("Wrong opcode for thread handle");
}
