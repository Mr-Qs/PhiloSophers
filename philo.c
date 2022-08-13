/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 01:18:25 by mrobaii           #+#    #+#             */
/*   Updated: 2022/08/13 21:08:50 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(char *str, int id, long t, t_philo *philo);
long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return(time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	shinigami(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->num_of_philos)
	{
		if (get_time() - philo[i].last_meal > philo->data->time_to_die)
		{
			ft_print("is dead", philo[i].id, philo[i].data->time, &philo[i]);
			pthread_mutex_lock(&philo->data->lck);
			return (1);
		}
		i++;
	}
	return (0);
}

void	mutex_init(t_data *data, int num_of_philo)
{
	int	i;

	i = 0;
	while (i < num_of_philo)
		pthread_mutex_init(&data->forks[i++], NULL);
	pthread_mutex_init(&data->lck, NULL);
	pthread_mutex_init(&data->meal, NULL);
}

void	ft_usleep(long time)
{
	long t;

	t = get_time();
	while(get_time() - t < time)
		usleep(100);
}

void	ft_print(char *str, int id, long t, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lck);
	printf("%ld ms %d %s\n", get_time() - t, id, str);
	pthread_mutex_unlock(&philo->data->lck);
}

void	ft_eating(t_philo *philo, long t)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	ft_print("has take a fork", philo->id, t, philo);
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	ft_print("has take a fork", philo->id, t, philo);
	ft_print("is eating", philo->id, t, philo);
	ft_usleep(philo->data->time_to_eat);
	philo->last_meal = get_time();
	pthread_mutex_lock(&philo->data->meal);
	philo->meals++;
	pthread_mutex_unlock(&philo->data->meal);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}

void	ft_sleeping(t_philo *philo, long t)
{
	ft_print("is sleeping", philo->id, t, philo);
	ft_usleep(philo->data->time_to_sleep);
}

void	*routine(void *ph)
{
	t_philo	*philo;


	philo = (t_philo*)ph;
	philo->data->time = get_time();
	while (1)
	{
		ft_eating(philo, philo->data->time);
		ft_sleeping(philo, philo->data->time);
		ft_print("is thinking", philo->id, philo->data->time, philo);
	}
}

int num_of_ats(t_philo *philo)
{
	int i;

	i = 0;
	if (philo->data->num_of_eats == -1)
		return 0;
	while (i < philo->data->num_of_philos)
	{
		pthread_mutex_lock(&philo->data->meal);
		if (philo[i].meals < philo->data->num_of_eats)
			 return (0);
		pthread_mutex_unlock(&philo->data->meal);
		i++;
	}
	return (1);
}

void	data_init(int ac, char **av, t_philo *philo)
{
	t_data	*data;
	int		i;

	i = 0;
	data = malloc(sizeof(t_data));
	data->forks = malloc(sizeof(pthread_mutex_t) * atoi(av[1]));
	mutex_init(data, atoi(av[1]));
	data->num_of_philos = atoi(av[1]);
	data->time_to_die = atoi(av[2]);
	data->time_to_eat = atoi(av[3]);
	data->time_to_sleep = atoi(av[4]);
	data->num_of_eats = -1;
	if (ac == 6)
		data->num_of_eats = atoi(av[5]);
	while (i < data->num_of_philos)
	{
		philo[i].meals = 0;
		philo[i].data = data;
		philo[i].id = i + 1;
		philo[i].left_fork = i;
		philo[i].right_fork = i + 1;
		philo[i].last_meal = get_time();
		if (i == data->num_of_philos - 1)
			philo[i].right_fork = 0;
		pthread_create(&(philo+i)->t, NULL, &routine, philo + i);
		usleep(50);
		i++;
	}
}
int main(int ac, char **av)
{
	t_philo *philo;

	philo = malloc(sizeof(t_philo) * atoi(av[1]));
	if (!philo)
		return (0);
	data_init(ac, av, philo);
	while (1)
	{
			printf("OK\n");

		if (num_of_ats(philo))
			return (0);
			printf("OK\n");
		if (shinigami(philo))
			return (0);
	}
}
