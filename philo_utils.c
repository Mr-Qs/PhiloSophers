/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucifer <lucifer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 04:09:57 by lucifer           #+#    #+#             */
/*   Updated: 2022/08/14 04:58:14 by lucifer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_atoi(char *str)
{
	int i;
	int	res;
	int sign;

	sign = 1;
	i = 0;
	res = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\r' || str[i] == '\v')
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

void	ft_usleep(long time)
{
	long t;

	t = get_time();
	while(get_time() - t < time)
		usleep(100);
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



void	ft_print(char *str, int id, long t, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lck);
	printf("%ld ms %d %s\n", get_time() - t, id, str);
	pthread_mutex_unlock(&philo->data->lck);
}