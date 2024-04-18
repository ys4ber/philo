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

// long	ft_get_time(void)
// {
// 	struct timeval	time;

// 	gettimeofday(&time, NULL);
// 	return (time.tv_sec * 1000 + time.tv_usec / 1000);
// }

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
    pthread_mutex_lock(philo->data->print);
    printf("%ld %d %s\n", ft_get_time() - philo->data->start_time, philo->id, str);
    pthread_mutex_unlock(philo->data->print);
}

void *routine(void *p)
{
    t_philo *philo;
    philo = (t_philo *)p;

    if (philo->id % 2 == 0)
        ft_usleep(50);

    while (!philo->is_full && !philo->is_over)
    {
        pthread_mutex_lock(philo->left_fork);

        ft_print(philo, "has taken a fork");
        
        pthread_mutex_lock(philo->right_fork);
        
        ft_print(philo, "has taken a fork");
        
        ft_print(philo, "is eating");
        
        ft_usleep(philo->data->time_to_eat);

        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);


        pthread_mutex_lock(philo->data->mutex1);
        philo->last_eat = ft_get_time();
        pthread_mutex_unlock(philo->data->mutex1);
        
       
        
        
        
        philo->nb_eat++;
        



        ft_print(philo, "is sleeping");
        ft_usleep(philo->data->time_to_sleep);
        ft_print(philo, "is thinking");
        

        pthread_mutex_lock(philo->data->mutex2);
        if (philo->data->nb_must_eat != -1 && philo->nb_eat >= philo->data->nb_must_eat)
            philo->is_full = 1;
        pthread_mutex_unlock(philo->data->mutex2);
    }
    return (NULL);
}

void ft_start_simulation(t_philo *philo)
{
    philo->data->start_time = ft_get_time();
    for (int i = 0; i < philo->data->nb_philo; i++)
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
    }
}

void ft_free_all(t_philo *philo)
{
    for (int i = 0; i < philo->data->nb_philo; i++)
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

int ft_monitor(t_philo *philo)
{
    while (1)
    {
        for (int i = 0; i < philo->data->nb_philo; i++)
        {
            pthread_mutex_lock(philo->data->mutex2);
            if (philo[i].data->nb_must_eat != -1 && philo[i].nb_eat >= philo[i].data->nb_must_eat)
                philo[i].is_full = 1;
            pthread_mutex_unlock(philo->data->mutex2);
            pthread_mutex_lock(philo->data->mutex1);   
            if (ft_get_time() - philo[i].last_eat > philo[i].data->time_to_die)
            {
                ft_print(&philo[i], "died");
                pthread_mutex_unlock(philo->data->mutex1);  
                return (1);
            }
            pthread_mutex_unlock(philo->data->mutex1); 
        }
    }
    return (0);
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
    
    philo->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * philo->data->nb_philo);
    if (!philo->forks)
        return (ft_error("Malloc failed"));
    for (int i = 0; i < philo->data->nb_philo; i++)
        pthread_mutex_init(&philo->forks[i], NULL);
    
    philo->data->print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    if (!philo->data->print)
        return (ft_error("Malloc failed"));
    pthread_mutex_init(philo->data->print, NULL);


    philo->data->mutex1 = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    if (!philo->data->mutex1)
        return (ft_error("Malloc failed"));
    pthread_mutex_init(philo->data->mutex1, NULL);

    philo->data->mutex2 = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    if (!philo->data->mutex2)
        return (ft_error("Malloc failed"));
    pthread_mutex_init(philo->data->mutex2, NULL);

    philo->data->mutex3 = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    if (!philo->data->mutex3)
        return (ft_error("Malloc failed"));
    pthread_mutex_init(philo->data->mutex3, NULL);

    philo->data->mutex4 = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    if (!philo->data->mutex4)
        return (ft_error("Malloc failed"));
    pthread_mutex_init(philo->data->mutex4, NULL);

    ft_start_simulation(philo);

    if (ft_monitor(philo))
        return (1);

    ft_free_all(philo);

    return (0);
    
}