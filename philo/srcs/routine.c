#include "../includes/philo.h"

static void *routine(void *args)
{
    t_data  *data;
    int     i1;
    int     i2;

    data = (t_data *)args;

}

int threading(t_data *data)
{
    int i;

    i = -1;
    while (i < data->philos_nbr)
    {
        safe_threads(&data->philos[i].thread_id, NULL, &routine, CREATE);
    }
}