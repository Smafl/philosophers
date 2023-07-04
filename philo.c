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

void	print_env(t_env *env)
{
    printf("num of philo %u\n", env->num_of_philo);
    printf("time to die %u\n", env->time_to_die);
    printf("time to eat %u\n", env->time_to_eat);
    printf("time to sleep %u\n", env->time_to_sleep);
    printf("num must eat %u\n", env->num_must_eat);
	printf("start time %lu\n", env->start_time);
}

// thinking -- time for waiting for forks
/*
- think unless the left fork is available; when it is, pick it up;
- think unless the right fork is available; when it is, pick it up;
- when both forks are held, eat for a fixed amount of time;
- put the left fork down;
- put the right fork down;
- repeat from the beginning.
*/
// void	*routine(void *add)
// {
// 	(void)*add;
// 	t_mutex	*mutex;
//
// 	mutex = (t_mutex *) add;
// 	pthread_mutex_lock(&mutex->mutex);
// 	printf("eating\n");
// 	usleep(3000);
// 	printf("sleeping\n");
// 	usleep(3000);
// 	printf("thinking\n");
// 	usleep(3000);
// 	pthread_mutex_unlock(&mutex->mutex);
// 	return (NULL);
// }

// pthread_create:
// thread, attributes of the thread, function, arguments for function
int	main(int argc, char **argv)
{
    // pthread_t		thread_1;
    // pthread_t		thread_2;
    // t_mutex			mutex;
    t_env			env;

    // (void)argc;
    // (void)argv;

    if (argc < 5 || argc > 6)
        return (printf("incorrect input\n"), 1);
    if (!init_env(argv, &env))
		return (1);
    // pthread_mutex_init(&mutex.mutex, NULL);
    // pthread_create(&thread_1, NULL, routine, &mutex);
    // pthread_create(&thread_2, NULL, routine, &mutex);
    // pthread_join(thread_1, NULL);
    // pthread_join(thread_2, NULL);
    // pthread_mutex_destroy(&mutex.mutex);
//    print_env(&env);
    return (0);
}

// use fsan for data races
