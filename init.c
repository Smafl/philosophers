/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 16:22:04 by ekulichk          #+#    #+#             */
/*   Updated: 2023/06/21 16:41:21 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
# include <stdbool.h>

t_env	*init_env(char **argv)
{
    t_env	*env;

    env = malloc(sizeof(t_env));
    if (env == NULL)
        exit(1);
    if (!parse_argv(env, argv))
    {
        printf("incorrect input\n");
        exit(1);
    }
    env->start_time = get_time();
    env->philos = malloc(sizeof(t_philo) * env->num_of_philo);
    env->forks = malloc(sizeof(pthread_mutex_t) * env->num_of_philo);
    if (!init_philos(env) || !init_forks(env))
        exit(1);
    env->is_dead = false;
    return (env);
}

bool	init_philos(t_env *env)
{
    (void)env;
    return true;
}

bool	init_forks(t_env *env)
{
    unsigned int i;

    i = 0;
    while (i != env->num_of_philo)
    {
        if (pthread_mutex_init(&env->forks[i], NULL))
            return (false);
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
