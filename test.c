
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

typedef struct s_mutex
{
	pthread_mutex_t mutex;
}	t_mutex;

 void	*routine(void *add)
 {
 	(void)*add;
 	t_mutex	*mutex;

 	mutex = (t_mutex *) add;
 	pthread_mutex_lock(&mutex->mutex);
 	printf("eating\n");
 	usleep(3000);
 	printf("sleeping\n");
 	usleep(3000);
 	printf("thinking\n");
 	usleep(3000);
 	pthread_mutex_unlock(&mutex->mutex);
 	return (NULL);
 }

// pthread_create:
// thread, attributes of the thread, function, arguments for function
int	main(int argc, char **argv)
{
	 pthread_t		thread_1;
	 pthread_t		thread_2;
	 t_mutex		mutex;
	 (void)argc;
	 (void)argv;

	 pthread_mutex_init(&mutex.mutex, NULL);
	 pthread_create(&thread_1, NULL, routine, &mutex);
	 pthread_create(&thread_2, NULL, routine, &mutex);
	 pthread_join(thread_1, NULL);
	 pthread_join(thread_2, NULL);
	 pthread_mutex_destroy(&mutex.mutex);
	return (0);
}
