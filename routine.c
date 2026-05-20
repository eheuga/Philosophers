#include "philo.h"


int is_dead (t_philo *philo){

    int flag;
    
    pthread_mutex_lock(&philo->data->someone_died_mutex);
    flag = philo->data->stop;
    pthread_mutex_unlock(&philo->data->someone_died_mutex);

    return (flag);

}

void* routine(void *args)
{

    t_philo * philo;
    philo = (t_philo *)args;
    
    if (philo->data->nb_philos == 1)
    {
        pthread_mutex_lock(philo->left_fork);
        print_action(philo, "has taken a fork");
        while(!is_dead(philo))
            ft_usleep(500, philo);
        return NULL;
    }
    if (philo->id % 2 == 0)
        usleep(1000); 
    

    while (!is_dead(philo)){
    
    
    pthread_mutex_lock(philo->left_fork);
    print_action(philo, "has taken a fork");
    pthread_mutex_lock(philo->right_fork);
    print_action(philo, "has taken a fork");

    print_action(philo, "is eating");
    pthread_mutex_lock(&philo->data->meal_mutex);
    
    philo->last_meal_time = get_time();
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->data->meal_mutex);

    ft_usleep (philo->data->time_to_eat, philo);

    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
    
    print_action(philo, "is sleeping");
    ft_usleep (philo->data->time_to_sleep, philo);

    print_action(philo, "is thinking");
    }

    return NULL;
}