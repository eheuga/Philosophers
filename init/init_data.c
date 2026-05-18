#include "../philo.h"

void init_data (t_data *data, int ac, char **av)
{
    data->nb_philos = atoi(av[1]);
    data->time_to_die = atoi(av[2]);
    data->time_to_eat = atoi(av[3]);
    data->time_to_sleep = atoi(av[4]);
    if (ac == 6)
        data->nb_of_meals = atoi(av[5]);
    else
        data->nb_of_meals = -1;

    data->philos = malloc(sizeof(t_philo) * data->nb_philos);
    data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
}