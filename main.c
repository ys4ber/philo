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
		usleep(50);
}
 
int ft_error(char *str)
{
    printf("Error: %s\n", str);
    return (1);
}

void ft_print(t_philo *philo, char *str)
{
    pthread_mutex_lock(philo->print);
    printf("%ld %d %s\n", ft_get_time() - philo->data->start_time, philo->id, str);
    pthread_mutex_unlock(philo->print);
}


void *routine(void *p)
{
    t_philo *philo;
    philo = (t_philo *)p;
    
    while (1)
    {
        pthread_mutex_lock(philo->left_fork);
        ft_print(philo, "has taken a fork");
        pthread_mutex_lock(philo->right_fork);
        ft_print(philo, "has taken a fork");
        ft_print(philo, "is eating");
        philo->last_eat = ft_get_time();
        ft_usleep(philo->data->time_to_eat);
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        ft_print(philo, "is sleeping");
        ft_usleep(philo->data->time_to_sleep);
        ft_print(philo, "is thinking");
    }
    return (NULL);
}



int main(int ac , char **av)
{
    if (ac != 5 && ac != 6)
        return (ft_error("Wrong number of arguments"));
    t_philo *philo;
    philo = malloc(sizeof(t_philo) * ft_atoi(av[1]));
    if (!philo)
        return (ft_error("Malloc failed"));
    philo->data = malloc(sizeof(t_data));
    if (!philo->data)
        return (ft_error("Malloc failed"));
    philo->data->nb_philo = ft_atoi(av[1]);
    philo->data->time_to_die = ft_atoi(av[2]);
    philo->data->time_to_eat = ft_atoi(av[3]);
    philo->data->time_to_sleep = ft_atoi(av[4]);
    philo->data->nb_must_eat = (ac == 6) ? ft_atoi(av[5]) : -1;
    philo->data->start_time = ft_get_time();
    philo->is_dead = 0;
    philo->is_full = 0;
    philo->is_over = 0;
    

    philo->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
        * philo->data->nb_philo);
    if (!philo->forks)
        return (ft_error("Malloc failed"));

    for (int i = 0; i < philo->data->nb_philo; i++)
        pthread_mutex_init(&philo->forks[i], NULL);
    
    philo->print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    if (!philo->print)
        return (ft_error("Malloc failed"));


    pthread_mutex_init(philo->print, NULL);

    for (int i = 0; i < philo->data->nb_philo; i++)
    {
        philo[i].id = i + 1;
        philo[i].is_dead = 0;
        philo[i].is_full = 0;
        philo[i].is_over = 0;
        philo[i].is_started = 0;
        philo[i].last_eat = philo->data->start_time;
        philo[i].nb_eat = 0;
        philo[i].data = philo->data;
        philo[i].print = philo->print;
        philo[i].forks = philo->forks;
        philo[i].left_fork = &philo->forks[i];
        philo[i].right_fork = &philo->forks[(i + 1) % philo->data->nb_philo];
    }

    for (int i = 0; i < philo->data->nb_philo; i++)
        pthread_create(&philo[i].philo, NULL, routine, &philo[i]);
    
    for (int i = 0; i < philo->data->nb_philo; i++)
        pthread_join(philo[i].philo, NULL);
}