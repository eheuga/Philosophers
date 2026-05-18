#include "../philo.h"

void init_mutex(t_data *data)
{
    int i = 0;

    while (i < data->nb_philos){
        pthread_mutex_init(&data->forks[i], NULL); 
        i++;
    }
}
