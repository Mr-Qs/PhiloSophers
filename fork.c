/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 01:48:33 by mrobaii           #+#    #+#             */
/*   Updated: 2022/08/24 04:27:04 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#include <semaphore.h>

typedef sem_t Semaphore;

Semaphore *make_semaphore(int value);

void semaphore_wait(Semaphore *semaphore);

void semaphore_signal(Semaphore *semaphore);

typedef sem_t Semaphore;

Semaphore *make_semaphore(int value){
          Semaphore *semaphore = (Semaphore *) malloc(sizeof(Semaphore));
          semaphore = sem_open("/semaphore", O_CREAT, 0644, value);
          sem_unlink("/semaphore");
          return semaphore;
}

void semaphore_wait(Semaphore *semaphore){
          sem_wait(semaphore);
}

void semaphore_signal(Semaphore *semaphore){
          sem_post(semaphore);
}

sem_t mutex;

void	*thread(void *args)
{
	sem_wait(&mutex);
	printf("\n Entred.. \n");
	sleep(10);
	printf("\n Just Exiting..\n");
	sem_post(&mutex);
	return (NULL);
}
int main()
{
	pthread_t t1, t2;
	
	sem_init(&mutex, 0, 1);
	pthread_create(&t1, NULL, thread, NULL);
	sleep(1);
	pthread_create(&t2, NULL, thread, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	sem_destroy(&mutex);
}