/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 20:24:21 by ekulichk          #+#    #+#             */
/*   Updated: 2023/07/26 03:31:31 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

void	join_threads(pthread_t *threads, unsigned int num_of_philo)
{
	unsigned int	i;

	i = 0;
	while (i != num_of_philo)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

void	destroy_mutexes(
	t_philo *philos, t_fork *forks, unsigned int num_of_philo)
{
	unsigned int	i;

	i = 0;
	while (i != num_of_philo)
	{
		pthread_mutex_destroy(&(forks + i)->mutex);
		i++;
	}
	pthread_mutex_destroy(&philos->env->print);
	pthread_mutex_destroy(&philos->env->dead);
}

void	free_all(t_philo *philos, pthread_t *threads, t_fork *forks)
{
	free(forks);
	free(threads);
	free(philos);
}
