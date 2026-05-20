#include "philo.h"

void ft_usleep (long long time_to_wait, t_philo *philo)
{
    long long t = get_time();
    while (get_time() - t < time_to_wait && !is_dead(philo))
        usleep(500);

    return ;

}