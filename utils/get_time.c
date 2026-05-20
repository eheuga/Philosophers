#include "philo.h"

long long get_time ()
{
    struct timeval t;
    long long result;

    gettimeofday(&t, NULL);
    result = (long long)t.tv_sec * 1000 + t.tv_usec / 1000;
    return (result);

}