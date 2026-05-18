#include "philo.h"


void* routine(void *args){

    t_philo * philo;
    
    philo = (t_philo *)args;
    if (philo->id % 2 == 0)
        usleep(1000); 
    while (1){
    pthread_mutex_lock(philo->left_fork);
    printf("Philo num %d took a fork\n", philo->id);
    pthread_mutex_lock(philo->right_fork);
    printf("Philo num %d took a fork\n", philo->id);
    printf("Philo num %d is eating\n", philo->id);
    usleep(philo->data->time_to_eat * 1000 );
    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
    printf("Philo num %d is sleeping\n", philo->id);
    usleep(philo->data->time_to_sleep * 1000 );

    printf("Philo num %d is thinking\n", philo->id);

    }

    return NULL;
}

int main (int ac, char** av)
{
    t_data data;

    (void)ac;
    init_data(&data, ac, av);
    init_mutex(&data);
    init_philos(&data);
    
    int i = 0;

    int N = data.nb_philos;

    while (i < N)
    {
        pthread_create(&data.philos[i].thread, NULL, routine, &data.philos[i]);
        i++;
    }
    
    i = 0;
    while (i < N){
        pthread_join(data.philos[i].thread, NULL);
        i++;

    }
    return 0;
}