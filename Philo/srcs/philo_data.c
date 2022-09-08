/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 21:32:56 by mrobaii           #+#    #+#             */
/*   Updated: 2022/09/06 01:51:23 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	data_init(int ac, char **av, t_philo *philo)
{
	t_data	*data;
	int		i;

	i = 0;
	data = malloc(sizeof(t_data));
	mutex_init(data, av);
	if (ac == 6)
		data->num_of_eats = ft_atoi(av[5]);
	while (i < data->num_of_philos)
	{
		philo[i].meals = 0;
		philo[i].data = data;
		philo[i].id = i + 1;
		philo[i].left_fork = i;
		philo[i].right_fork = i + 1;
		if (i == data->num_of_philos - 1)
			philo[i].right_fork = 0;
		pthread_create(&philo[i].t, NULL, &routine, &philo[i]);
		usleep(70);
		i++;
	}
}

void	mutex_init(t_data *data, char **av)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	data->num_of_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->num_of_eats = -1;
	while (i < ft_atoi(av[1]))
		pthread_mutex_init(&data->forks[i++], NULL);
	pthread_mutex_init(&data->lck, NULL);
	pthread_mutex_init(&data->meal, NULL);
}
