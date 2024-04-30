/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaber <ysaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:42:18 by ysaber            #+#    #+#             */
/*   Updated: 2024/04/30 18:39:05 by ysaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	pthread_mutex_t	*print;

	pthread_mutex_t	*mutex1;
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
	pthread_mutex_t	*r_fork;
}					t_philo;

// ft_utils.c
int					ft_atoi(const char *str);
int					ft_error(char *str);
bool				ft_check_validity(int ac, char **av);
int					ft_strlen(char *str);
int					count_full_philosophers(t_philo *philo);

// ft_sleep.c
int					ft_fill_data(t_philo *philo, int ac, char **av);
long				ft_get_time(void);
void				ft_usleep(long time);

// ft_utils1.c
void				ft_print(t_philo *philo, char *str);
void				ft_eat(t_philo *philo);
void				ft_free_all(t_philo *philo);
void				ft_print_dead(t_philo *philo);
int					ft_free(t_philo *philo);

#endif