#include "philo.h"

int ft_atoi(const char *str)
{
    int i;
    int sign;
    int res;

    i = 0;
    sign = 1;
    res = 0;
    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
        || str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
        i++;
    if (str[i] == '-')
        sign = -1;
    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i] >= '0' && str[i] <= '9')
    {
        res = res * 10 + str[i] - '0';
        i++;
    }
    return (res * sign);
}

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
 
int ft_error(char *str)
{
    printf("Error: %s\n", str);
    return (1);
}

bool ft_check_validity(int ac, char **av)
{
    int i;
    int j;

    i = 1;
    while (i < ac)
    {
        j = 0;
        while (av[i][j])
        {
            if (av[i][j] < '0' || av[i][j] > '9')
                return (true);
            j++;
        }
        i++;
    }
    return (false);
}

int ft_fill_data(t_philo *philo, int ac, char **av)
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