/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 10:31:39 by ekulichk          #+#    #+#             */
/*   Updated: 2023/07/13 14:58:19 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void	*routine(void *argv)
{
	t_philo			*philo;
	unsigned long	last_meal;
	unsigned int	num_of_meals;

	philo = argv;
	last_meal = philo->env->start_time;
	num_of_meals = 0;
	 while (!philo->env->is_dead)
	 {
		if (thinking(philo, last_meal))
			break;
		last_meal = get_time();
		if (eating(philo, &num_of_meals))
			break;
		if (sleeping(philo, last_meal))
			break;
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
//		free_philos(&philos);
		return (1);
	}
//	free_all(&philos, threads, forks);
	join_threads(philos, threads);
//	destroy_mutexes(philos, forks);
	return (0);
}
