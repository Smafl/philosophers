
#include "philo.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

bool    take_fork(t_fork *fork,unsigned int time_out)
{
	while (get_time() <= time_out)
	{
		pthread_mutex_lock(&fork->mutex);
		if (!fork->taken)
		{
			fork->taken = true;
			return (true);
		}
		pthread_mutex_unlock(&fork->mutex);
		usleep(100);
	}
	return (false);
}

void    unlock_fork(t_fork *fork)
{
	fork->taken = false;
	pthread_mutex_unlock(&fork->mutex);
}

void	print_log(unsigned int time, t_philo *philo, char *str)
{
	if (!philo->env->is_dead)
	{
		pthread_mutex_lock(&philo->env->print);
		printf("%u %u %s\n", time, philo->id, str);
		pthread_mutex_unlock(&philo->env->print);
	}
}

int check_if_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->dead);
	if (philo->env->is_dead)
	{
		pthread_mutex_unlock(&philo->env->dead);
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&philo->env->dead);
	return (EXIT_SUCCESS);
}

void	time_to_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->dead);
	if (!philo->env->is_dead)
		print_log(get_time() - philo->env->start_time, philo, "\033[0;31mdied\033[0m");
	philo->env->is_dead = true;
	pthread_mutex_unlock(&philo->env->dead);
}
