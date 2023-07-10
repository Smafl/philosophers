
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

unsigned int	get_time(void)
{
	struct timeval	time_now;

	gettimeofday(&time_now, NULL);
	return (time_now.tv_sec * 1000 + time_now.tv_usec / 1000);
}

void	print_log(unsigned int ph_nbr, char *str)
{
	printf("%u %u %s\n", get_time(), ph_nbr, str);
}

void	print_malloc_failed(void)
{
	printf("malloc failed\n");
	exit(1);
}
/*
 * 100ms time to die
 * 1000ms time to sleep
 *
 *
 */