
#include "philo.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

void	join_threads(t_philo *philos, pthread_t *threads)
{
	unsigned int i;

	i = 0;
	while (i != philos->env->num_of_philo)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

void	destroy_mutexes(t_philo *philos, pthread_mutex_t *forks)
{
	unsigned int i;

	i = 0;
	while (i != philos->env->num_of_philo)
	{
		pthread_mutex_destroy(forks + i);
		i++;
	}
	pthread_mutex_destroy(&philos->env->print);
}

void	free_philos(t_philo **philos)
{
//	printf("%p\n", philos);
	while (*philos)
	{
//		printf("philo address %p\n", *philos);
//		printf("%u\n", (*philos)->id);
		free(philos);
		philos++;
	}
//	free(philos);
//	philos = NULL;
}

void	free_all(t_philo **philos, pthread_t *threads, pthread_mutex_t *forks)
{
//	(void)forks;
//	(void)threads;
	join_threads(*philos, threads);
	destroy_mutexes(*philos, forks);
//	free_philos(philos);
}
