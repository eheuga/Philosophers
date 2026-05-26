#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct s_data    t_data;
typedef struct s_philo   t_philo;

struct s_philo
{
    int             id;              // 1 à N
    int             meals_eaten;     // compteur
    long long       last_meal_time;  // timestamp ms du dernier repas
    pthread_mutex_t *left_fork;      // pointeur vers le mutex
    pthread_mutex_t *right_fork;     // pointeur vers le mutex
    t_data          *data;           // accès aux données partagées
    pthread_t       thread;          // l'identifiant pthread
};

struct s_data
{
    int             nb_philos;
    long            time_to_die;
    long            time_to_eat;
    long            time_to_sleep;
    int             nb_of_meals;        // -1 si pas fourni
    long long       start_time;
    int             stop;
    pthread_mutex_t *forks;             // tableau de N mutex
    pthread_mutex_t meal_mutex ;        // nmutex
    pthread_mutex_t someone_died_mutex; // flag (on protégera avec mutex plus tard)
    pthread_mutex_t print_mutex;        // mutex de print
    t_philo         *philos;            // tableau de N philos
};

long long get_time ();
void init_data (t_data *data, int ac, char **av);
void init_philos(t_data *data);
void init_mutex(t_data *data);
void* routine(void *args);
int is_dead (t_philo *philo);
void print_action (t_philo *data, char *action);
void ft_usleep (long long time_to_wait, t_philo *philo);
int take_forks(t_philo *philo);
int check_stop(t_data *data);
void free_all(t_data *data);
void ft_think(t_philo *philo);

#endif
