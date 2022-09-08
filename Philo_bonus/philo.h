/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 01:24:11 by mrobaii           #+#    #+#             */
/*   Updated: 2022/09/08 02:32:08 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include<stdio.h>
# include<unistd.h>
# include<stdlib.h>
# include<pthread.h>
# include<semaphore.h>
# include<sys/time.h>
# include<signal.h>

typedef struct s_data
{
	int	num_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_of_eats;
}	t_data;

typedef struct s_philo
{
	int			id;
	long		last_meal;
	int			meals;
	int			ac;
	t_data		*data;
	long		time;
	pthread_t	t;
	sem_t		*forks;
	sem_t		*print;
}	t_philo;

long	get_time(void);
void	ft_usleep(long time);
int		ft_strlen(char *str);
void	ft_print(char *str, t_philo *philo);
int		ft_atoi(char *str);
void	sumulation(t_philo *philo, sem_t *forks);
void	data_init(t_philo *philo, t_data *data, int ac, char **av);
void	*shinigami(void *args);
void	killprocess(int num_of_philo, int *pid);
#endif