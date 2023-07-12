/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 10:31:39 by ekulichk          #+#    #+#             */
/*   Updated: 2023/07/04 17:41:25 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

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
		// change exit!
		if (thinking(philo, last_meal))
			exit(1);
		if (eating(philo, &num_of_meals))
			exit(1);
		last_meal = get_time();
		if (sleeping(philo, last_meal))
			exit(1);
	}
	return (NULL);
 }

// pthread_create:
// thread, attributes of the thread, function, arguments for function
int	main(int argc, char **argv)
{
	int 			i;
    t_env			env;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_t		*thread;

    if (argc < 5 || argc > 6)
        return (printf("incorrect input\n"), 1);
    if (!init_env(argv, &env, &philos, &forks))
		return (printf("mutex init failed\n"), 1);
	if (!thread_creation(&thread, &env, philos))
		return (printf("thread init failed\n"), 1);
	i = 0;
	while (i != env.num_of_philo)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
    return (0);
}
