#include "philo.h"

void init_mutex(t_data *data)
{
    int i = 0;

    while (i < data->nb_philos){
        pthread_mutex_init(&data->forks[i], NULL); 
        i++;
    }
    pthread_mutex_init(&data->print_mutex, NULL);
    pthread_mutex_init(&data->meal_mutex, NULL);
    pthread_mutex_init(&data->someone_died_mutex, NULL);
    
}
