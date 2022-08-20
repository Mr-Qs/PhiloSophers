/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 01:23:42 by mrobaii           #+#    #+#             */
/*   Updated: 2022/08/20 01:13:04 by mrobaii          ###   ########.fr       */
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

long	get_time()
{
	struct timeval time;
	
	gettimeofday(&time, NULL);

	return(time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_print(char *str, t_philo *philo)
{
	printf("%ld %d %s\n", get_time() - philo->time, philo->id, str);
}

void	ft_eating(t_philo *philo)
{
	ft_print("has take a fork", philo);
	ft_print("has take a fork", philo);
	ft_print("is eating", philo);
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
	philo->time = get_time();
	while (1)
	{
		ft_eating(philo);
	}
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
		philo->id = i + 1;
		if (pid == 0){
			routine(philo);
		if (pid == 0)
			break;
		i++;
	}

}
}
