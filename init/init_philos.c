#include "../philo.h"

void init_philos(t_data *data)
{

    int i = 0;
    while (i < data->nb_philos){
        data->philos[i].id = i + 1;
        data->philos[i].meals_eaten = 0;
        data->philos[i].last_meal_time = 0;
        data->philos[i].left_fork = &data->forks[i];
        data->philos[i].right_fork = &data->forks[(i + 1) % data->nb_philos];
        data->philos[i].data = data;
        //printf("Philo nb : %d\nLeft Fork : %p\nRight Fork : %p\n", data->philos[i].id,  (void *)data->philos[i].left_fork, (void *)data->philos[i].right_fork);
        i++;
    }

}