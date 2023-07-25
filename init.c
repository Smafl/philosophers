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
	unsigned int	inited;

	inited = 0;
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
		pthread_mutex_destroy(&env->print);
		printf("mutex init failed\n");
		return (false);
	}
    if (!init_forks(forks, env->num_of_philo, &inited))
	{
		printf("mutex init failed\n");
		destroy_mutexes(*philos, *forks, inited);
		return (false);
	}
	init_philos(philos, env, *forks);
    return (true);
}

bool    init_forks(t_fork **forks, unsigned int num_of_philo, unsigned int *inited)
{
	unsigned int	i;

	i = 0;
	while (i != num_of_philo)
	{
		if (pthread_mutex_init(&(*forks + i)->mutex, NULL))
		{
			*inited = i;
			return (false);
		}
		(*forks + i)->taken = false;
		i++;
	}
	return (true);
}

void    init_philos(t_philo **philos, t_env *env, t_fork *forks)
{
	unsigned int	i;
	t_philo			*ph;

	*philos = malloc(sizeof(t_philo) * env->num_of_philo);
	if (*philos == NULL)
		print_malloc_failed();
	i = 0;
	while (i != env->num_of_philo)
	{
		ph = *philos + i;
		ph->id = i + 1;
		ph->env = env;
		ph->l_fork = forks + i;
		ph->r_fork = forks + ((i + 1) % env->num_of_philo);
		i++;
	}
}

bool	thread_creation(pthread_t **threads, t_env *env, t_philo *philos)
{
	unsigned int 	i;

	*threads = malloc(sizeof(pthread_t) * env->num_of_philo);
	if (*threads == NULL)
		print_malloc_failed();
	i = 0;
	if (philos->env->num_of_philo == 1)
	{
		if (pthread_create(*threads, NULL, &lonely_routine, philos))
			return (printf("thread init failed\n"), false);
		return (true);
	}
	while (i != env->num_of_philo)
	{
		if (pthread_create(*threads + i, NULL, &routine, philos + i))
		{
			join_threads(*threads, i);
			return (printf("thread init failed\n"), false);
		}
		i++;
	}
	return (true);
}
