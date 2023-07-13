
#include "philo.h"
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

unsigned int	get_time(void)
{
	struct timeval	time_now;

	gettimeofday(&time_now, NULL);
	return (time_now.tv_sec * 1000 + time_now.tv_usec / 1000);
}

void	print_log(unsigned int time, unsigned int ph_nbr, char *str)
{
	printf("%u %u %s\n", time, ph_nbr, str);
}

void	print_malloc_failed(void)
{
	printf("malloc failed\n");
	exit(1);
}

void	pick_up_fork(t_philo *philo, int nbr)
{
	if (nbr == 1)
	{
		if (philo->id == philo->env->num_of_philo)
			pthread_mutex_lock(philo->r_fork);
		else
			pthread_mutex_lock(philo->l_fork);
	}
	else
	{
		if (philo->id == philo->env->num_of_philo)
			pthread_mutex_lock(philo->l_fork);
		else
			pthread_mutex_lock(philo->r_fork);
	}
}
