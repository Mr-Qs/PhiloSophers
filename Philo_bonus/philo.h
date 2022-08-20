/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 01:24:11 by mrobaii           #+#    #+#             */
/*   Updated: 2022/08/20 01:10:09 by mrobaii          ###   ########.fr       */
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
	sem_t	sem;
	t_data	*data;
	long	time;
}	t_philo;
#endif