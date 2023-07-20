
#include "philo.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void    unlock_fork(t_fork *fork)
{
	fork->taken = false;
	pthread_mutex_unlock(&fork->mutex);
}

bool    take_fork(t_fork *fork, unsigned int time_out)
{
	while (get_time() < time_out)
	{
		if (!fork->taken)
		{
			pthread_mutex_lock(&fork->mutex);
			fork->taken = true;
			return (true);
		}
		usleep(1000);
	}
	return (false);
}

int thinking(t_philo *philo, unsigned long last_meal)
{
	print_log(get_time() - philo->env->start_time, philo, "\033[0;34mis thinking\033[0m");
	if (!take_fork(philo->l_fork, last_meal + philo->env->time_to_die))
	{
		print_log(get_time() - philo->env->start_time, philo, "\033[0;31mdied think 1\033[0m");
		philo->env->is_dead = true;
		return (EXIT_FAILURE);
	}
	print_log(get_time() - philo->env->start_time, philo, "has taken a fork");
	if (!take_fork(philo->r_fork, last_meal + philo->env->time_to_die))
	{
		print_log(get_time() - philo->env->start_time, philo, "\033[0;31mdied think 2\033[0m");
		unlock_fork(philo->l_fork);
		philo->env->is_dead = true;
		return (EXIT_FAILURE);
	}
	print_log(get_time() - philo->env->start_time, philo, "has taken a fork");
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
			unlock_fork(philo->l_fork);
			unlock_fork(philo->r_fork);
			return (EXIT_FAILURE);
		}
	}
	unlock_fork(philo->l_fork);
	unlock_fork(philo->r_fork);
	return (EXIT_SUCCESS);
}

int sleeping(t_philo *philo, unsigned long last_meal)
{
	unsigned long	sleeping_time;
	unsigned long   slept;

	(void)last_meal;
	slept = 0;
	if (philo->env->time_to_sleep + philo->env->time_to_eat < philo->env->time_to_die)
		sleeping_time = philo->env->time_to_sleep;
	else
		sleeping_time = philo->env->time_to_die - philo->env->time_to_eat;
	print_log(get_time() - philo->env->start_time, philo, "\033[30;1mis sleeping\033[0m");
	while (!philo->env->is_dead && slept != sleeping_time)
	{
		usleep(1000);
		slept++;
	}
	if (sleeping_time > philo->env->time_to_sleep + philo->env->time_to_eat)
	{
		print_log(get_time() - philo->env->start_time, philo, "\033[0;31mdied sleep\033[0m");
		philo->env->is_dead = true;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
