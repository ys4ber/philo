#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_must_eat;
	long			start_time;
	int				is_dead;
	pthread_mutex_t	*last_meal;
	pthread_mutex_t	*last_eat_time;
	pthread_mutex_t	*print;

	pthread_mutex_t	*mutex1;
	pthread_mutex_t	*mutex2;
	pthread_mutex_t	*mutex3;
	pthread_mutex_t	*mutex4;

}					t_data;

typedef struct s_philo
{
	int				id;

	int				is_dead;
	int				is_full;
	int				is_over;
	int				is_started;
	long			last_eat;
	int				nb_eat;

	pthread_t		philo;
	t_data			*data;

	pthread_mutex_t	*forks;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}					t_philo;

int					ft_atoi(const char *str);
long				ft_get_time(void);
void				ft_usleep(long time);
int					ft_error(char *str);
bool				ft_check_validity(int ac, char **av);

// ft_file1.c
int					ft_fill_data(t_philo *philo, int ac, char **av);
void				ft_print(t_philo *philo, char *str);
int					ft_free(t_philo *philo);
void				ft_free_all(t_philo *philo);
void				ft_eat(t_philo *philo);

#endif