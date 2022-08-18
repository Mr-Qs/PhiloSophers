/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 01:23:42 by mrobaii           #+#    #+#             */
/*   Updated: 2022/08/18 23:58:39 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_atoi(char *str)
{
	int	i;
	int	res;
	int	sign;

	sign = 1;
	i = 0;
	res = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\r' || str[i] == '\v')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + str[i++] - '0';
	if (ft_strlen(str + i) > 0)
		return (0);
	return (res * sign);
}

void	routine(t_philo *philo)
{
	
}
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
}
int	main(int ac, char **av)
{
	t_philo	*philo;
	t_data *data;
	int i;
	int	pid;
	i =0;
	philo = malloc(sizeof(t_philo));
	data = malloc(sizeof(t_data));
	data_init(philo, data, ac, av);
	while (i < data->num_of_philo)
	{
		pid = fork();
		if (pid == 0){
			routine(&i);
		if (pid == 0)
			break;
		i++;
	}
}
