/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 16:22:04 by ekulichk          #+#    #+#             */
/*   Updated: 2023/07/07 17:20:17 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>

bool	init_env(char **argv, t_env *env, t_philo **philos, t_fork	**forks)
{
	if (!parse_argv(env, argv))
	{
		printf("incorrect input\n");
		return (false);
    }
    env->start_time = get_time();
	env->is_dead = false;
	if (pthread_mutex_init(&env->print, NULL))
	{
		printf("mutex init failed\n");
		return (false);
	}
	if (pthread_mutex_init(&env->dead, NULL))
	{
		printf("mutex init failed\n");
		return (false);
	}
    if (!init_forks(forks, env->num_of_philo))
	{
		printf("mutex init failed\n");
		return (false);
	}
	init_philos(philos, env, *forks);
    return (true);
}

bool    init_forks(t_fork **forks, unsigned int num_of_philo)
{
	unsigned int i;

	*forks = malloc(sizeof(t_fork) * num_of_philo);
	if (*forks == NULL)
		print_malloc_failed();
	i = 0;
	while (i != num_of_philo)
	{
		if (pthread_mutex_init(&(*forks + i)->mutex, NULL))
		{
			// todo
			// destroy already inited mutexes
			return (false);
		}
		(*forks + i)->taken = false;
		i++;
	}
	return (true);
}

void    init_philos(t_philo **philos, t_env *env, t_fork *forks)
{
	unsigned int i;
	t_philo *ph;

	*philos = malloc(sizeof(t_philo) * env->num_of_philo);
	if (*philos == NULL)
		print_malloc_failed();
	i = 0;
	while (i != env->num_of_philo)
	{
		ph = *philos + i;
//		printf("ph address %p\n", ph);
		ph->id = i + 1;
		ph->env = env;
		ph->activity = THINK;
		ph->activity_start = get_time();
		ph->l_fork = forks + i;
		ph->r_fork = forks + ((i + 1) % env->num_of_philo);
		i++;
	}
}

bool	thread_creation(pthread_t **thread, t_env *env, t_philo *philos)
{
	unsigned int 	i;

	*thread = malloc(sizeof(pthread_t) * env->num_of_philo);
	if (*thread == NULL)
		print_malloc_failed();
	i = 0;
	while (i != env->num_of_philo)
	{
		if (pthread_create(*thread + i, NULL, &routine, philos + i))
		{
			// todo
			// join already inited threads and mutexes
			return (printf("thread init failed\n"), false);
		}
		i++;
	}
	return (true);
}
