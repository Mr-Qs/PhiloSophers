/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 01:18:25 by mrobaii           #+#    #+#             */
/*   Updated: 2022/09/06 01:51:57 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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

	philo = (t_philo *)ph;
	philo->time = get_time();
	philo->last_meal = get_time();
	while (1)
	{
		ft_eating(philo, philo->time);
		ft_sleeping(philo, philo->time);
		ft_print("is thinking", philo->id, philo->time, philo);
	}
}

int	num_of_ats(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->data->num_of_eats == -1)
		return (0);
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

int	main(int ac, char **av)
{
	t_philo	*philo;

	if (ac < 5 || ft_atoi(av[1]) <= 0 || ft_atoi(av[2]) <= 0
		|| ft_atoi(av[3]) <= 0 || ft_atoi(av[4]) <= 0)
	{
		printf("Argument Error\n");
		return (0);
	}
	if (ac == 6 && ft_atoi(av[5]) <= 0)
	{
		printf("Argument Error\n");
		return (0);
	}
	philo = malloc(sizeof(t_philo) * ft_atoi(av[1]));
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
