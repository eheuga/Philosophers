#include "philo.h"

int take_forks(t_philo *philo){



	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
		if (is_dead(philo)){
			pthread_mutex_unlock(philo->right_fork);
			return (1);
		}
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		if (is_dead(philo)){
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
			return (1);
		}
	}

	else {
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		if (is_dead(philo)){
			pthread_mutex_unlock(philo->left_fork);
			return (1);
		}
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
		if (is_dead(philo)){
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			return (1);
		}
	}


    return (0);
}

void ft_think(t_philo *philo)
{
    long long think_time;

    print_action(philo, "is thinking");
    think_time = (philo->data->time_to_die - philo->data->time_to_eat
            - philo->data->time_to_sleep) / 2;
    if (think_time < 0)
        think_time = 0;
    if (think_time > 0)
        ft_usleep(think_time, philo);
}

