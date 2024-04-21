/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaber <ysaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 22:17:21 by ysaber            #+#    #+#             */
/*   Updated: 2024/04/21 22:17:22 by ysaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_fill_data(t_philo *philo, int ac, char **av)
{
	if (ft_check_validity(ac, av) == true)
		return (1);
	philo->data->nb_philo = ft_atoi(av[1]);
	philo->data->time_to_die = ft_atoi(av[2]);
	philo->data->time_to_eat = ft_atoi(av[3]);
	philo->data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		philo->data->nb_must_eat = ft_atoi(av[5]);
	else
		philo->data->nb_must_eat = -1;
	philo->data->is_dead = 0;
	return (0);
}

void	ft_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->data->print);
	printf("%ld %d %s\n", ft_get_time() - philo->data->start_time, philo->id,
		str);
	pthread_mutex_unlock(philo->data->print);
}

int	ft_free(t_philo *philo)
{
	ft_free_all(philo);
	return (1);
}

void	ft_free_all(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->nb_philo)
	{
		pthread_join(philo[i].philo, NULL);
		pthread_mutex_destroy(&philo->forks[i]);
	}
	pthread_mutex_destroy(philo->data->print);
	free(philo->forks);
	free(philo->data->print);
	free(philo->data);
	free(philo);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	ft_print(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	ft_print(philo, "has taken a fork");
	pthread_mutex_lock(philo->data->mutex1);
	philo->last_eat = ft_get_time();
	pthread_mutex_unlock(philo->data->mutex1);
	ft_print(philo, "is eating");
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(philo->data->mutex1);
	philo->nb_eat++;
	pthread_mutex_unlock(philo->data->mutex1);
}
