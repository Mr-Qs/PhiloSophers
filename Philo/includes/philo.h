/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 01:09:49 by mrobaii           #+#    #+#             */
/*   Updated: 2022/09/06 02:25:16 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>

typedef struct s_data
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_eats;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lck;
	pthread_mutex_t	meal;
}	t_data;

typedef struct s_philo
{
	int			id;
	int			left_fork;
	int			right_fork;
	int			meals;
	long		last_meal;
	pthread_t	t;
	t_data		*data;
	long		time;
}	t_philo;
int		ft_atoi(char *str);
long	get_time(void);
int		shinigami(t_philo *philo);
void	ft_usleep(long time);
void	mutex_init(t_data *data, char **av);
void	ft_print(char *str, int id, long t, t_philo *philo);
void	ft_eating(t_philo *philo, long t);
void	ft_sleeping(t_philo *philo, long t);
void	*routine(void *ph);
int		num_of_ats(t_philo *philo);
void	data_init(int ac, char **av, t_philo *philo);
int		ft_strlen(char *str);
#endif