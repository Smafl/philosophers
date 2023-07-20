
#include "philo.h"
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

void	print_log(unsigned int time, t_philo *philo, char *str)
{
	if (!philo->env->is_dead)
	{
		pthread_mutex_lock(&philo->env->print);
		printf("%u %u %s\n", time, philo->id, str);
		pthread_mutex_unlock(&philo->env->print);
	}
}

unsigned int	get_time(void)
{
	struct timeval	time_now;

	gettimeofday(&time_now, NULL);
	return (time_now.tv_sec * 1000 + time_now.tv_usec / 1000);
}

void	print_malloc_failed(void)
{
	printf("malloc failed\n");
	exit(1);
}
