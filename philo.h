#pragma once


#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>



typedef struct s_data
{
    int nb_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int nb_must_eat;
    long start_time;
    
} t_data;

typedef struct s_philo
{
    int id;
    
    int is_dead;
    int is_full;
    int is_over;
    int is_started;
    int last_eat;
    int nb_eat;

    pthread_t philo;
    t_data *data;
    pthread_mutex_t *last_eat_time;
    pthread_mutex_t *print;
    pthread_mutex_t *forks;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
} t_philo;




// typedef struct s_data
// {
//     int nb_philo;
//     int time_to_die;
//     int time_to_eat;
//     int time_to_sleep;
//     int nb_must_eat;
//     int is_dead;
//     int is_full;
//     int is_over;
//     int is_started;
//     long start_time;

//     int nb_eat;

//     struct timeval start;
//     pthread_mutex_t print;
//     pthread_t thread;
//     pthread_mutex_t *forks;
//     pthread_mutex_t *left_fork;
//     pthread_mutex_t *right_fork;
// } t_data;

// typedef struct s_philo
// {
//     int id;
//     t_data *data;
// } t_philo;