/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaber <ysaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:42:59 by ysaber            #+#    #+#             */
/*   Updated: 2024/04/23 12:43:01 by ysaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->data->mutex1);
	if (philo->data->is_dead == 1)
	{
		pthread_mutex_unlock(philo->data->mutex1);
		return ;
	}
	if (philo->data->is_dead == 0)
	{
		pthread_mutex_lock(philo->data->print);
		printf("%ld %d %s\n", ft_get_time() - philo->data->start_time,
			philo->id, str);
		pthread_mutex_unlock(philo->data->print);
	}
	pthread_mutex_unlock(philo->data->mutex1);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	ft_print(philo, "has taken a fork");
	pthread_mutex_lock(philo->r_fork);
	ft_print(philo, "has taken a fork");
	ft_print(philo, "is eating");
	pthread_mutex_lock(philo->data->mutex1);
	philo->last_eat = ft_get_time();
	pthread_mutex_unlock(philo->data->mutex1);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_lock(philo->data->mutex1);
	philo->nb_eat++;
	pthread_mutex_unlock(philo->data->mutex1);
}

void	ft_free_all(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->nb_philo)
	{
		pthread_join(philo[i].philo, NULL);
		pthread_mutex_destroy(&philo->forks[i]);
		i++;
	}
	pthread_mutex_destroy(philo->data->print);
	pthread_mutex_destroy(philo->data->mutex1);
	free(philo->data->mutex1);
	free(philo->forks);
	free(philo->data->print);
	free(philo->data);
	free(philo);
}

void	ft_print_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->data->print);
	printf("%ld %d died\n", ft_get_time()
		- philo->data->start_time, philo->id);
	pthread_mutex_unlock(philo->data->print);
}

int	ft_free(t_philo *philo)
{
	ft_free_all(philo);
	return (1);
}
