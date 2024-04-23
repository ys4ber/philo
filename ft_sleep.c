/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaber <ysaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:42:24 by ysaber            #+#    #+#             */
/*   Updated: 2024/04/23 11:43:32 by ysaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(long time)
{
	long	start;

	start = ft_get_time();
	while (ft_get_time() - start < time)
		usleep(500);
}

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
