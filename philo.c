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
#include <unistd.h>

//void	print_env(t_env *env)
//{
//    printf("num of philo %u\n", env->num_of_philo);
//    printf("time to die %u\n", env->time_to_die);
//    printf("time to eat %u\n", env->time_to_eat);
//    printf("time to sleep %u\n", env->time_to_sleep);
//    printf("num must eat %u\n", env->num_must_eat);
//	printf("start time %lu\n", env->start_time);
//}

// thinking -- time for waiting for forks
/*
- think unless the left fork is available; when it is, pick it up;
- think unless the right fork is available; when it is, pick it up;
- when both forks are held, eat for a fixed amount of time;
- put the left fork down;
- put the right fork down;
- sleep;
- repeat from the beginning.
*/

 void	*routine(void *argv)
 {
	t_philo			*philo;
	unsigned long	last_meal;
	unsigned int	eaten;


	philo = argv;
	last_meal = philo->env->start_time;
	eaten = 0;
	while (!philo->env->is_dead)
	{
		log(philo->id, "is thinking");
		pthread_mutex_lock(philo->l_fork);
		if (get_time() - last_meal > philo->env->time_to_die)
		{
			log(philo->id, "died");
			pthread_mutex_unlock(philo->l_fork);
			philo->env->is_dead = true;
			exit (1);
		}
		log(philo->id, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
		if (get_time() - last_meal > philo->env->time_to_die)
		{
			log(philo->id, "died");
			pthread_mutex_unlock(philo->r_fork);
			pthread_mutex_unlock(philo->l_fork);
			philo->env->is_dead = true;
			exit (1);
		}
		log(philo->id, "has taken a fork");
		last_meal = get_time();
		log(philo->id, "is eating");
		usleep(philo->env->time_to_eat * 1000);
		eaten += 1;
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		if (eaten == philo->env->num_must_eat)
			break ;
		log(philo->id, "is sleeping");
		usleep(philo->env->time_to_sleep * 1000);
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
	thread = malloc(sizeof(pthread_t) * env.num_of_philo);
	if (thread == NULL)
	{
		printf("malloc failed\n");
		exit(1);
	}
	i = 0;
	while (i != env.num_of_philo)
	{
		if (pthread_create(thread + i, NULL, &routine, philos + i))
		{
			// разделить на чет/нечет
			// join already inited threads
			return (printf("thread init failed\n"), 1);
		}
		i++;
	}
	i = 0;
	while (i != env.num_of_philo)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
//    print_env(&env);
    return (0);
}

// use fsan for data races
