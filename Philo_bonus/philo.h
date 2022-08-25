/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 01:24:11 by mrobaii           #+#    #+#             */
/*   Updated: 2022/08/25 17:38:12 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
# define PHILO_H

# include<stdio.h>
# include<unistd.h>
# include<stdlib.h>
# include<pthread.h>
#include<semaphore.h>
#include<sys/time.h>
#include<signal.h>

typedef struct s_data
{
	int	num_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_of_eats;
	sem_t	semaphore;
}	t_data;

typedef struct s_philo
{
	int 	id;
	long 	last_meal;
	t_data	*data;
	long	time;
	pthread_t t;
	sem_t	*death;
}	t_philo;
#endif