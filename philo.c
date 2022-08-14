/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucifer <lucifer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 01:18:25 by mrobaii           #+#    #+#             */
/*   Updated: 2022/08/14 04:18:31 by lucifer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eating(t_philo *philo, long t)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	ft_print("has take a fork", philo->id, t, philo);
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	ft_print("has take a fork", philo->id, t, philo);
	ft_print("is eating", philo->id, t, philo);
	philo->last_meal = get_time();
	ft_usleep(philo->data->time_to_eat);
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
		{
			pthread_mutex_unlock(&philo->data->meal);
			return (0);	
		}
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
		if (num_of_ats(philo))
			return (0);
		if (shinigami(philo))
			return (0);
	}
}
