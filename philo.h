/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 01:09:49 by mrobaii           #+#    #+#             */
/*   Updated: 2022/08/02 01:17:38 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>

typedef	struct s_data
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_eats;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lck;
	pthread_mutex_t meal;
	long			time;
}	t_data;

typedef	struct s_philo
{
	int			id;
	int			left_fork;
	int			right_fork;
	int  		meals;
	long			last_meal;
	pthread_t	t;
	t_data		*data;
}	t_philo;
#endif