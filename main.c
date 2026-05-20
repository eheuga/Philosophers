#include "philo.h"


int main (int ac, char** av)
{
    t_data data;

    (void)ac;
    data.start_time = get_time();

    init_data(&data, ac, av);
    init_mutex(&data);
    init_philos(&data);
    
    int i = 0;
    long long last_meal;
    long long time_check;
    int meal_count;
    int full;

    while (i < data.nb_philos)
    {
        pthread_create(&data.philos[i].thread, NULL, routine, &data.philos[i]);
        i++;
    }
    
    while (!data.stop){
        i = 0;
        full = 0;
        while (i < data.nb_philos)
        {
            pthread_mutex_lock(&data.meal_mutex);
            last_meal = data.philos[i].last_meal_time;
            meal_count = data.philos[i].meals_eaten;
            pthread_mutex_unlock(&data.meal_mutex);
            if (meal_count >= data.nb_of_meals && data.nb_of_meals != -1)
                full++;
            time_check = get_time() - last_meal;
            if (time_check > data.time_to_die){
                pthread_mutex_lock(&data.print_mutex);
                printf("%lld %d died\n", get_time() - data.start_time, data.philos[i].id);
                pthread_mutex_unlock(&data.print_mutex);
                pthread_mutex_lock(&data.someone_died_mutex);
                data.stop = 1;
                pthread_mutex_unlock(&data.someone_died_mutex);
                break;
            }
            i++;
        }
        if (full == data.nb_philos){
            pthread_mutex_lock(&data.someone_died_mutex);
            data.stop = 1;
            pthread_mutex_unlock(&data.someone_died_mutex);
            break;
        }    
        usleep(500);
    }

    i = 0;
    while (i < data.nb_philos)
    {
        pthread_join(data.philos[i].thread, NULL);
        i++;
    }
    return 0;
}