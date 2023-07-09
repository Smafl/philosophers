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
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>

bool	init_env(char **argv, t_env *env, t_philo **philos, pthread_mutex_t	**forks)
{
	if (!parse_argv(env, argv))
	{
		printf("incorrect input\n");
        exit(1);
    }
    env->start_time = get_time();
	env->is_dead = false;
    if (!init_forks(forks, env->num_of_philo))
		return (false);
	init_philos(philos, env, *forks);
    return (true);
}

bool    init_forks(pthread_mutex_t	**forks, unsigned int num_of_philo)
{
	unsigned int i;

	*forks = malloc(sizeof(pthread_mutex_t) * num_of_philo);
	if (*forks == NULL)
	{
		printf("malloc failed\n");
		exit(1);
	}
	i = 0;
	while (i != num_of_philo)
	{
		if (pthread_mutex_init(*forks + i, NULL))
		{
			// destroy already inited mutexes
			return (false);
		}
		i++;
	}
	return (true);
}

void    init_philos(t_philo **philos, t_env *env, pthread_mutex_t *forks)
{
	unsigned int i;
	t_philo *ph;

	*philos = malloc(sizeof(t_philo) * env->num_of_philo);
	if (*philos == NULL)
	{
		printf("malloc failed\n");
		exit(1);
	}
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

unsigned int	get_time(void)
{
    struct timeval	time_now;

    gettimeofday(&time_now, NULL);
    return (time_now.tv_sec * 1000 + time_now.tv_usec / 1000);
}

void	log(unsigned int ph_nbr, char *str)
{
	printf("%u %u %s\n", get_time(), ph_nbr, str);
}