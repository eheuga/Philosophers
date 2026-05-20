#include "philo.h"

void print_action (t_philo *philo, char *action)
{

    long long t;
    
    t = get_time() - philo->data->start_time;
    
    pthread_mutex_lock(&philo->data->print_mutex);
    if (!is_dead(philo))
        printf("%lld %d %s\n",t, philo->id, action);
    pthread_mutex_unlock(&philo->data->print_mutex);

    return ;
}