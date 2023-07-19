
#include "philo.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int thinking(t_philo *philo, unsigned long last_meal)
{
//	unsigned long	thinking_time;

//	thinking_time = 0;
	print_log(get_time() - philo->env->start_time, philo, "\033[0;34mis thinking\033[0m");
//	while (!philo->env->is_dead && (get_time() - last_meal < philo->env->time_to_die))
	while (!philo->env->is_dead)
	{
		usleep(1000);
//		thinking_time++;
		pthread_mutex_lock(philo->l_fork);
		if (get_time() - last_meal > philo->env->time_to_die)
		{
			print_log(get_time() - philo->env->start_time, philo, "\033[0;31mdied think 1\033[0m");
			pthread_mutex_unlock(philo->l_fork);
			philo->env->is_dead = true;
			return (EXIT_FAILURE);
		}
		print_log(get_time() - philo->env->start_time, philo, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
		if (get_time() - last_meal > philo->env->time_to_die)
		{
			print_log(get_time() - philo->env->start_time, philo, "\033[0;31mdied think 2\033[0m");
			pthread_mutex_unlock(philo->r_fork);
			pthread_mutex_unlock(philo->l_fork);
			philo->env->is_dead = true;
			return (EXIT_FAILURE);
		}
		else
		{
			print_log(get_time() - philo->env->start_time, philo, "has taken a fork");
			break ;
		}
	}
	return  (EXIT_SUCCESS);
}

int eating(t_philo *philo, unsigned int *num_of_meals)
{
	print_log(get_time() - philo->env->start_time, philo, "\033[0;32mis eating\033[0m");
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
	pthread_mutex_unlock(philo->r_fork);
	return (EXIT_SUCCESS);
}

int sleeping(t_philo *philo, unsigned long last_meal)
{
	unsigned long	sleeping_time;

	sleeping_time = 0;
	print_log(get_time() - philo->env->start_time, philo, "\033[30;1mis sleeping\033[0m");
	while (sleeping_time < philo->env->time_to_sleep && !philo->env->is_dead)
	{
		usleep(1000);
		sleeping_time++;
		if (get_time() - last_meal > philo->env->time_to_die)
		{
			print_log(get_time() - philo->env->start_time, philo, "\033[0;31mdied sleep\033[0m");
			philo->env->is_dead = true;
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
