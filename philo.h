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
    int is_dead;
    
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
    pthread_mutex_t *last_meal;
    pthread_mutex_t *last_eat_time;
    pthread_mutex_t *print;
    pthread_mutex_t *forks;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
} t_philo;



// #pragma once


// #include <pthread.h>
// #include <semaphore.h>
// #include <stdlib.h>
// #include <stdio.h>
// #include <unistd.h>
// #include <time.h>
// #include <sys/time.h>



// typedef struct s_philo_info
// {
// 	long	start_time;
// 	int		number_of_philo;
// 	int		time_to_die;
// 	int		time_to_eat;
// 	int		time_to_sleep;
// 	int		number_of_meals;
// }	t_philo_info;

// // typedef struct s_data
// // {
// // 	pthread_mutex_t	*forks;
// // 	pthread_mutex_t	print;
// // 	pthread_mutex_t	*meals;
// // 	pthread_mutex_t	last_meal_check;
// // }	t_data;

// typedef struct s_philo
// {
// 	int				philo_id;
// 	long			last_meal;
// 	int				maels;

// 	pthread_t		thread;

//     pthread_mutex_t	*forks;
// 	pthread_mutex_t	print;
// 	pthread_mutex_t	*meals;
// 	pthread_mutex_t	last_meal_check;
// 	pthread_mutex_t	*left_fork;
// 	pthread_mutex_t	*right_fork;

// 	t_philo_info	info;
	
// }	t_philo;