
#include "philo.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int thinking(t_philo *philo, unsigned long last_meal)
{
	print_log(get_time() - philo->env->start_time, philo->id, "\033[0;34mis thinking\033[0m");
	while (1)
	{
//		pick_up_fork(philo, 1);
		if (philo->id == philo->env->num_of_philo)
		{
			pthread_mutex_lock(philo->r_fork);
			printf("[id %d] taken fork: %p\n", philo->id, philo->r_fork);
		}
		else
		{
			pthread_mutex_lock(philo->l_fork);
			printf("[id %d] taken fork: %p\n", philo->id, philo->l_fork);
		}
		if (get_time() - last_meal > philo->env->time_to_die)
		{
			print_log(get_time() - philo->env->start_time, philo->id, "\033[0;31mdied\033[0m");
			pthread_mutex_unlock(philo->l_fork);
			philo->env->is_dead = true;
			return (EXIT_FAILURE);
		}
		print_log(get_time() - philo->env->start_time, philo->id, "has taken a fork");
//		pick_up_fork(philo, 2);
		if (philo->id == philo->env->num_of_philo)
		{
			pthread_mutex_lock(philo->l_fork);
			printf("[id %d] taken fork: %p\n", philo->id, philo->l_fork);
		}
		else
		{
			pthread_mutex_lock(philo->r_fork);
			printf("[id %d] taken fork: %p\n", philo->id, philo->r_fork);
		}
		if (get_time() - last_meal > philo->env->time_to_die)
		{
			print_log(get_time() - philo->env->start_time, philo->id, "\033[0;31mdied\033[0m");
			pthread_mutex_unlock(philo->r_fork);
			pthread_mutex_unlock(philo->l_fork);
			philo->env->is_dead = true;
			return (EXIT_FAILURE);
		}
		else
		{
			print_log(get_time() - philo->env->start_time, philo->id, "has taken a fork");
			break ;
		}
	}
	return  (EXIT_SUCCESS);
}

int eating(t_philo *philo, unsigned int *num_of_meals)
{
	print_log(get_time() - philo->env->start_time, philo->id, "\033[0;32mis eating\033[0m");
	usleep(philo->env->time_to_eat * 1000);
	if (philo->env->num_must_eat != 0)
	{
		*num_of_meals += 1;
		if (*num_of_meals == philo->env->num_must_eat)
		{
			pthread_mutex_unlock(philo->l_fork);
			pthread_mutex_unlock(philo->r_fork);
			return (EXIT_FAILURE);
		}
	}
	pthread_mutex_unlock(philo->l_fork);
	printf("[id %d] release fork: %p\n", philo->id, philo->r_fork);
	pthread_mutex_unlock(philo->r_fork);
	printf("[id %d] release fork: %p\n", philo->id, philo->r_fork);
	return (EXIT_SUCCESS);
}

int sleeping(t_philo *philo, unsigned long last_meal)
{
	unsigned long	sleeping;

	print_log(get_time() - philo->env->start_time, philo->id, "\033[30;1mis sleeping\033[0m");
	sleeping = 0;
	while (sleeping < philo->env->time_to_sleep)
	{
		usleep(5000);
		sleeping += 1;
		if (get_time() - last_meal > philo->env->time_to_die)
		{
			print_log(get_time() - philo->env->start_time, philo->id, "\033[0;31mdied\033[0m");
			philo->env->is_dead = true;
			exit(1);
		}
	}
	return (EXIT_SUCCESS);
}
