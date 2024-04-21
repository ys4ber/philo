/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaber <ysaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 22:17:26 by ysaber            #+#    #+#             */
/*   Updated: 2024/04/21 22:17:27 by ysaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->id % 2 == 0)
		ft_usleep(60);
	while (1)
	{
		pthread_mutex_lock(philo->data->mutex1);
		if (philo->data->nb_must_eat != -1
			&& philo->nb_eat >= philo->data->nb_must_eat)
			philo->is_full = 1;
		pthread_mutex_unlock(philo->data->mutex1);
		pthread_mutex_lock(philo->data->mutex1);
		if (philo->is_full)
		{
			pthread_mutex_unlock(philo->data->mutex1);
			break ;
		}
		pthread_mutex_unlock(philo->data->mutex1);
		ft_eat(philo);
		ft_print(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
		ft_print(philo, "is thinking");
	}
	return (NULL);
}

void	ft_start_simulation(t_philo *philo)
{
	int	i;

	philo->data->start_time = ft_get_time();
	i = 0;
	while (i < philo->data->nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].is_full = 0;
		philo[i].is_over = 0;
		philo[i].is_started = 0;
		philo[i].last_eat = ft_get_time();
		philo[i].nb_eat = 0;
		philo[i].data = philo->data;
		philo[i].forks = philo->forks;
		philo[i].left_fork = &philo->forks[i];
		philo[i].right_fork = &philo->forks[(i + 1) % philo->data->nb_philo];
		pthread_create(&philo[i].philo, NULL, routine, &philo[i]);
		i++;
	}
}

void	ft_monitoring(t_philo *philo)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < philo->data->nb_philo)
		{
			pthread_mutex_lock(philo->data->mutex1);
			if (ft_get_time() - philo[i].last_eat > philo[i].data->time_to_die)
			{
				printf("\033[0;31m");
				pthread_mutex_lock(philo->data->print);
				printf("%ld %d %s\n", ft_get_time() - philo->data->start_time,
					philo[i].id, "is dead");
				printf("\033[0m");
				pthread_mutex_unlock(philo->data->mutex1);
				return ;
			}
			pthread_mutex_unlock(philo->data->mutex1);
			i++;
		}
		usleep(1000);
	}
}

int	ft_init_mutexes(t_philo *philo)
{
	int	i;

	philo->data->print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!philo->data->print)
		return (1);
	pthread_mutex_init(philo->data->print, NULL);
	philo->data->mutex1 = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!philo->data->mutex1)
		return (1);
	pthread_mutex_init(philo->data->mutex1, NULL);
	philo->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* philo->data->nb_philo);
	if (!philo->forks)
		return (1);
	i = 0;
	while (i < philo->data->nb_philo)
	{
		pthread_mutex_init(&philo->forks[i], NULL);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_philo	*philo;

	if (ac != 5 && ac != 6)
		return (ft_error("Wrong number of arguments"));
	philo = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	if (!philo)
		return (ft_error("Malloc failed"));
	philo->data = malloc(sizeof(t_data));
	if (!philo->data)
		return (ft_error("Malloc failed"));
	if (ft_fill_data(philo, ac, av) == 1)
		return (ft_error("Invalid arguments or malloc failed"));
	if (ft_init_mutexes(philo) == 1)
		return (ft_error("Mutex init failed"));
	ft_start_simulation(philo);
	ft_monitoring(philo);
	pthread_mutex_lock(philo->data->mutex1);
	if (philo->is_dead == 1 || philo->is_full == 1)
	{
		pthread_mutex_unlock(philo->data->mutex1);
		return (ft_free(philo));
	}
	pthread_mutex_unlock(philo->data->mutex1);
	return (0);
}
