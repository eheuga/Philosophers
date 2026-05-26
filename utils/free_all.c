#include "philo.h"

void free_all(t_data *data){

	int i = 0;

	while (i < data->nb_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->meal_mutex);
	pthread_mutex_destroy(&data->someone_died_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	free(data->forks);
	free(data->philos);
}
