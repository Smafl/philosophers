/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 16:22:04 by ekulichk          #+#    #+#             */
/*   Updated: 2023/07/04 16:01:28 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

 void	*routine(void *argv)
 {
	 t_fork	*fork;

	 fork = (t_fork *) argv;
	pthread_mutex_lock(&fork->mutex);
	fork->is_loked = true;
	printf("is loked %d\n", fork->is_loked);
	printf("hi");
	usleep(3000);
	pthread_mutex_unlock(&fork->mutex);
	fork->is_loked = false;
	printf("is loked %d\n", fork->is_loked);
// 	printf("eating\n");
// 	printf("sleeping\n");
// 	printf("thinking\n");
	return (NULL);
 }

bool	init_env(char **argv, t_env *env)
{
	if (!parse_argv(env, argv))
	{
		printf("incorrect input\n");
        exit(1);
    }
    env->philos = malloc(sizeof(t_philo) * env->num_of_philo);
    if (env->philos == NULL)
    {
		printf("malloc failed\n");
        exit(1);
	}
    env->start_time = get_time();
    env->is_dead = false;
    if (!init_forks(env) || !init_philos(env))
		return (false);
    return (true);
}

bool    init_philos(t_env *env)
{
	unsigned int i;

	i = 0;
	while (i != env->num_of_philo)
	{
		env->philos->id = i;
		if (pthread_create(&env->philos->thread, NULL, routine, &env->philos[i].fork.mutex))
			return (false);
		i++;
	}
	return (true);
}

bool    init_forks(t_env *env)
{
	unsigned int i;

	i = 0;
	while (i != env->num_of_philo)
	{
		if (pthread_mutex_init(&env->philos[i].fork.mutex, NULL))
			return (false);
		env->philos[i].fork.is_loked = false;
		i++;
	}
	return (true);
}

unsigned int	get_time(void)
{
    struct timeval	time_now;

    gettimeofday(&time_now, NULL);
    return (time_now.tv_sec * 1000 + time_now.tv_usec / 1000);
}
