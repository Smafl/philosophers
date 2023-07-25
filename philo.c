/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 10:31:39 by ekulichk          #+#    #+#             */
/*   Updated: 2023/07/24 23:55:50 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void	*lonely_routine(void *argv)
{
	t_philo			*philo;

	philo = argv;
	print_log(get_time() - philo->env->start_time, philo, "\033[0;34mis thinking\033[0m");
	pthread_mutex_lock(&philo->r_fork->mutex);
	print_log(get_time() - philo->env->start_time, philo, "has taken a fork");
	pthread_mutex_unlock(&philo->r_fork->mutex);
	usleep(philo->env->time_to_die * 1000);
	print_log(get_time() - philo->env->start_time, philo, "\033[0;31mdied\033[0m");
	return (NULL);
}

void	*routine(void *argv)
{
	t_philo			*philo;
	unsigned long	last_meal;
	unsigned int	num_of_meals;

	philo = argv;
	if (philo->id % 2 == 0)
		usleep(philo->env->time_to_eat * 1000);
	last_meal = philo->env->start_time;
	num_of_meals = 0;
	while (!philo->env->is_dead)
	{
		if (thinking(philo, last_meal))
			break ;
		if (eating(philo, &num_of_meals, &last_meal))
			break ;
		if (sleeping(philo, last_meal))
			break ;
	}
	return (NULL);
}

// pthread_create:
// thread, attributes of the thread, function, arguments for function
int	main(int argc, char **argv)
{
    t_env			env;
	t_fork          *forks;
	t_philo			*philos;
	pthread_t		*threads;

    if (argc < 5 || argc > 6)
        return (printf("incorrect input\n"), 1);
    if (!init_env(argv, &env, &philos, &forks))
		return (1);
	if (!thread_creation(&threads, &env, philos))
	{
		destroy_mutexes(philos, forks, env.num_of_philo);
		free_all(philos, threads);
		return (1);
	}
	join_threads(threads, env.num_of_philo);
	destroy_mutexes(philos, forks, env.num_of_philo);
	free_all(philos, threads);
	return (0);
}
