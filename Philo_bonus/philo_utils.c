/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 02:26:36 by mrobaii           #+#    #+#             */
/*   Updated: 2022/09/08 03:32:27 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	data_init(t_philo *philo, t_data *data, int ac, char **av)
{
	int	i;

	i = 0;
	data->num_of_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->num_of_eats = -1;
	if (ac == 6)
		data->num_of_eats = ft_atoi(av[5]);
	philo->data = data;
	philo->time = get_time();
	philo->last_meal = get_time();
	philo->meals = 0;
	philo->ac = ac;
}

void	killprocess(int num_of_philo, int *pid)
{
	int	i;

	i = 0;
	while (i < num_of_philo)
		kill(pid[i++], SIGKILL);
}

int	checker(int ac, char **av)
{
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
	return (1);
}
