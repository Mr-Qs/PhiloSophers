/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 22:48:29 by mrobaii           #+#    #+#             */
/*   Updated: 2022/09/08 02:27:18 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine(t_philo *philo, sem_t *forks)
{
	while (1)
	{
		sem_wait(forks);
		ft_print("has take a fork", philo);
		sem_wait(forks);
		ft_print("has take a fork", philo);
		ft_print("is eating", philo);
		philo->last_meal = get_time();
		ft_usleep(philo->data->time_to_eat);
		philo->meals++;
		sem_post(forks);
		sem_post(forks);
		ft_print("is sleeping", philo);
		ft_usleep(philo->data->time_to_sleep);
		ft_print("is thinking", philo);
	}
}

void	*shinigami(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (1)
	{
		if (get_time() - philo->last_meal >= philo->data->time_to_die)
		{
			sem_wait(philo->print);
			printf("%ld ms %d is dead\n", get_time() - philo->time, philo->id);
			exit(1);
		}
		if (philo->ac == 6 && philo->meals >= philo->data->num_of_eats)
			exit(0);
	}	
}

void	creating_philos(t_philo *philo, int *pid)
{
	int	i;
	int	id;

	i = 0;
	while (i < philo->data->num_of_philo)
	{
		philo->id = i + 1;
		id = fork();
		if (id)
			pid[i] = id;
		if (id == 0)
		{
			pthread_create(&philo->t, NULL, &shinigami, philo);
			routine(philo, philo->forks);
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_data	*data;
	int		*pid;
	int		catch;

	pid = malloc(sizeof(int) * ft_atoi(av[1]));
	philo = malloc(sizeof(t_philo));
	data = malloc(sizeof(t_data));
	sem_unlink("/FORKS");
	sem_unlink("/PRINT");
	data_init(philo, data, ac, av);
	philo->forks = sem_open("/FORKS", O_CREAT, 777, data->num_of_philo);
	philo->print = sem_open("/PRINT", O_CREAT, 777, 1);
	creating_philos(philo, pid);
	while (waitpid(-1, &catch, 0) != -1)
	{
		if (catch == 256)
			killprocess(data->num_of_philo, pid);
	}
}
