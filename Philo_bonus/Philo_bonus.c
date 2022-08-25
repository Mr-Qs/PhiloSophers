/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 22:48:29 by mrobaii           #+#    #+#             */
/*   Updated: 2022/08/25 17:43:09 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#include "philo.h"

long	get_time()
{
	struct timeval time;
	
	gettimeofday(&time, NULL);

	return(time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(long time)
{
	long t;

	t = get_time();
	while (get_time() - t < time)
		usleep(100);
}
int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}


void	ft_print(char *str, t_philo *philo)
{
	printf("%ld %d %s\n", get_time() - philo->time, philo->id, str);
}

void	sumulation(t_philo *philo, sem_t *sema)
{
	sem_wait(sema);
	philo->last_meal = get_time();
	ft_print("has take a fork", philo);
	sem_wait(sema);
	ft_print("has take a fork", philo);
	ft_print("is eating", philo);
	ft_usleep(philo->data->time_to_eat);
	sem_post(sema);
	sem_post(sema);
	ft_print("is sleeping", philo);
	ft_usleep(philo->data->time_to_sleep);
	ft_print("is thinking", philo);
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

void	routine(t_philo *philo, sem_t *sema)
{
	philo->time = get_time(); 
	while (1)
	{
		sumulation(philo, sema);
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
	philo->last_meal = get_time();
}

void	*shinigami(void *args)
{
	sem_t *death;
	t_philo *philo;

	philo = (t_philo *)args;
	death = philo->death;
	while (1)
	{
		if (get_time() - philo->last_meal >= philo->data->time_to_die)
		{
			sem_post(death);
			ft_print("is dead", philo);
		}
	}	
}
int	main(int ac, char **av)
{
	t_philo	*philo;
	t_data *data;
	int i;
	int	id;
	int *pid;
	sem_t	*sema;
	
	pid = malloc(sizeof(int) * ft_atoi(av[1]));
	sem_unlink("/SEMA");
	sem_unlink("/DEATH");
	i = 0;
	philo = malloc(sizeof(t_philo));
	data = malloc(sizeof(t_data));
	data_init(philo, data, ac, av);
	sema = sem_open("/SEMA", O_CREAT, 777, data->num_of_philo);
	philo->death = sem_open("/DEATH", O_CREAT, 777, 0);
	while (i < data->num_of_philo)
	{
		philo->id = i + 1;
		id = fork();
		if (id)
			pid[i] = id;
		if (id == 0)
		{
			pthread_create(&philo->t, NULL, &shinigami, philo->death);
			routine(philo, sema);
		}
		usleep(90);
		i++;
	}
	sem_wait(philo->death);
	i = 0;
	while (i < philo->data->num_of_philo)
		kill(pid[i++], SIGKILL);
	waitpid(0, &i, WNOHANG);
}