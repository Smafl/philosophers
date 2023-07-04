
#ifndef PHILO_PHILO_H
#define PHILO_PHILO_H

# include <pthread.h>
# include <stdbool.h>

typedef enum e_act
{
    EAT,
    SLEEP,
    THINK,
}   t_act;

typedef struct s_fork
{
    pthread_mutex_t mutex;
	bool            is_loked;
}	t_fork;

typedef struct s_philo
{
    unsigned int   		id;
	pthread_t        	thread;
    t_fork             fork;
	t_act               act;
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
    bool			is_dead;
}	t_env;

// init.c 4
bool        	init_env(char **argv, t_env *env);
bool            init_philos(t_env *env);
bool            init_forks(t_env *env);
unsigned int	get_time(void);

// parse_input.c 3
bool			parse_argv(t_env *env, char **argv);
bool			ph_atoi(const char *str, unsigned int *result);

#endif
