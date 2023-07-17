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
		 print_log(get_time() - philo->env->start_time, philo->id, "\033[0;34mis thinking\033[0m");
		 pthread_mutex_lock(philo->l_fork);
		 if (get_time() - last_meal > philo->env->time_to_die)
		 {
			 print_log(get_time() - philo->env->start_time, philo->id, "\033[0;31mdied\033[0m");
			 pthread_mutex_unlock(philo->l_fork);
			 philo->env->is_dead = true;
			 exit (1);
		 }
		 print_log(get_time() - philo->env->start_time, philo->id, "has taken a fork");
		 pthread_mutex_lock(philo->r_fork);
		 if (get_time() - last_meal > philo->env->time_to_die)
		 {
			 print_log(get_time() - philo->env->start_time, philo->id, "\033[0;31mdied\033[0m");
			 pthread_mutex_unlock(philo->r_fork);
			 pthread_mutex_unlock(philo->l_fork);
			 philo->env->is_dead = true;
			 exit (1);
		 }
		 print_log(get_time() - philo->env->start_time, philo->id, "has taken a fork");
		 last_meal = get_time();
		 print_log(get_time() - philo->env->start_time, philo->id, "\033[0;32mis eating\033[0m");
		 usleep(philo->env->time_to_eat * 1000);
		 if (philo->env->num_must_eat != 0)
		 {
			 num_of_meals += 1;
			 if (num_of_meals == philo->env->num_must_eat)
			 {
				 pthread_mutex_unlock(philo->l_fork);
				 pthread_mutex_unlock(philo->r_fork);
				 break ;
			 }
		 }
		 pthread_mutex_unlock(philo->l_fork);
//		 printf("[id %d] release fork: %p\n", philo->id, philo->r_fork);
		 pthread_mutex_unlock(philo->r_fork);
//		 printf("[id %d] release fork: %p\n", philo->id, philo->r_fork);
		 print_log(get_time() - philo->env->start_time, philo->id, "\033[30;1mis sleeping\033[0m");
		 usleep(philo->env->time_to_sleep * 1000);
	 }
//	while (!philo->env->is_dead)
//	{
//		// change exit!
//		if (thinking(philo, last_meal))
//			exit(1);
//		if (eating(philo, &num_of_meals))
//			exit(1);
//		last_meal = get_time();
//		if (sleeping(philo, last_meal))
//			exit(1);
//	}
	return (NULL);
 }

void	free_all(t_philo **philos, pthread_t **threads, pthread_mutex_t	**forks)
{
	unsigned int i;

	i = 0;
	while (i != (*philos)->env->num_of_philo)
	{
		pthread_join(*threads[i], NULL);
		i++;
	}
	i = 0;
	while (i != (*philos)->env->num_of_philo)
	{
		pthread_mutex_destroy(*forks + i);
		i++;
	}
}

// pthread_create:
// thread, attributes of the thread, function, arguments for function
int	main(int argc, char **argv)
{
    t_env			env;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_t		*threads;

    if (argc < 5 || argc > 6)
        return (printf("incorrect input\n"), 1);
    if (!init_env(argv, &env, &philos, &forks))
		return (printf("mutex init failed\n"), 1);
	if (!thread_creation(&threads, &env, philos))
		return (printf("thread init failed\n"), 1);
	free_all(&philos, &threads, &forks);
    return (0);
}
