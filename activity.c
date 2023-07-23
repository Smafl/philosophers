
#include "philo.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void    unlock_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	fork->taken = false;
	pthread_mutex_unlock(&fork->mutex);
}

bool    take_fork(t_fork *fork, unsigned int time_out)
{
	while (get_time() <= time_out)
	{
		if (!fork->taken)
		{
			pthread_mutex_lock(&fork->mutex);
			fork->taken = true;
			pthread_mutex_unlock(&fork->mutex);
			return (true);
		}
		usleep(100);
	}
	return (false);
}

int thinking(t_philo *philo, unsigned long last_meal)
{
	print_log(get_time() - philo->env->start_time, philo, "\033[0;34mis thinking\033[0m");
	if (!take_fork(philo->l_fork, last_meal + philo->env->time_to_die))
	{
		print_log(get_time() - philo->env->start_time, philo, "\033[0;31mdied think 1\033[0m");
		pthread_mutex_lock(&philo->env->dead);
		philo->env->is_dead = true;
		pthread_mutex_unlock(&philo->env->dead);
		return (EXIT_FAILURE);
	}
	print_log(get_time() - philo->env->start_time, philo, "has taken a left fork");
	if (!take_fork(philo->r_fork, last_meal + philo->env->time_to_die))
	{
		print_log(get_time() - philo->env->start_time, philo, "\033[0;31mdied think 2\033[0m");
		pthread_mutex_lock(&philo->env->dead);
		philo->env->is_dead = true;
		pthread_mutex_unlock(&philo->env->dead);
		unlock_fork(philo->l_fork);
		return (EXIT_FAILURE);
	}
	print_log(get_time() - philo->env->start_time, philo, "has taken a right fork");
	return  (EXIT_SUCCESS);
}

int sleeping_2(t_philo *philo, unsigned long last_meal)
{
	unsigned long	sleep_start;

	(void)last_meal;
	sleep_start = get_time();
	while ((get_time() - sleep_start < philo->env->time_to_eat) && !philo->env->is_dead)
	{
		if (get_time() - sleep_start >= philo->env->time_to_die)
		{
			print_log(get_time() - philo->env->start_time, philo, "\033[0;31mdied sleep\033[0m");
			pthread_mutex_lock(&philo->env->dead);
			philo->env->is_dead = true;
			pthread_mutex_unlock(&philo->env->dead);
			return (EXIT_FAILURE);
		}
		if (philo->env->is_dead)
			return (EXIT_FAILURE);
		usleep(100);
	}
	return (EXIT_SUCCESS);
}

int eating(t_philo *philo, unsigned int *num_of_meals, unsigned long *last_meal)
{
	*last_meal = get_time();
	print_log(get_time() - philo->env->start_time, philo, "\033[0;32mis eating\033[0m");
	sleeping_2(philo, *last_meal);
	usleep(philo->env->time_to_eat * 1000);
	if (philo->env->num_must_eat != 0)
	{
		*num_of_meals += 1;
		if (*num_of_meals == philo->env->num_must_eat)
		{
			unlock_fork(philo->l_fork);
			unlock_fork(philo->r_fork);
			return (EXIT_FAILURE);
		}
	}
	unlock_fork(philo->l_fork);
	unlock_fork(philo->r_fork);
	return (EXIT_SUCCESS);
}

// todo
// doesn't work case ./philo 4 410 200 200 -- nobody should die

int sleeping(t_philo *philo, unsigned long last_meal)
{
	unsigned long	sleep_start;

	(void)last_meal;
	sleep_start = get_time();
	print_log(get_time() - philo->env->start_time, philo, "\033[30;1mis sleeping\033[0m");
	while ((get_time() - sleep_start < philo->env->time_to_sleep) && !philo->env->is_dead)
	{
		if (get_time() - sleep_start >= philo->env->time_to_die)
		{
			print_log(get_time() - philo->env->start_time, philo, "\033[0;31mdied sleep\033[0m");
			pthread_mutex_lock(&philo->env->dead);
			philo->env->is_dead = true;
			pthread_mutex_unlock(&philo->env->dead);
			return (EXIT_FAILURE);
		}
		if (philo->env->is_dead)
			return (EXIT_FAILURE);
		usleep(100);
	}
	return (EXIT_SUCCESS);
}
