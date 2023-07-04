
#ifndef PHILO_PHILO_H
#define PHILO_PHILO_H

# include <pthread.h>
# include <stdbool.h>

typedef struct s_mutex
{
    pthread_mutex_t mutex;
}	t_mutex;

typedef struct s_philo
{
    int   		philo_id;
    pthread_t 	thread_id;
}	t_philo;

typedef struct s_environment
{
    unsigned int 	num_of_philo;
    unsigned int 	time_to_die;
    unsigned int 	time_to_eat;
    unsigned int 	time_to_sleep;
    unsigned int 	num_must_eat;
    unsigned long	start_time;
    t_philo 		*philos;
    pthread_mutex_t	*forks;
    bool			is_dead;
}	t_env;


// init.c 4
t_env			*init_env(char **argv);
bool		    init_philos(t_env *env);
bool		    init_forks(t_env *env);
unsigned int	get_time(void);


// parse_input.c 3
bool			parse_argv(t_env *env, char **argv);
bool			ph_atoi(const char *str, unsigned int *result);

#endif
