
#ifndef PHILO_PHILO_H
#define PHILO_PHILO_H

# include <pthread.h>
# include <stdbool.h>

typedef struct s_environment
{
    unsigned int 	num_of_philo;
    unsigned int 	time_to_die;
    unsigned int 	time_to_eat;
    unsigned int 	time_to_sleep;
    unsigned int 	num_must_eat;
    unsigned long	start_time;
	bool			is_dead;
}	t_env;

typedef struct s_philo
{
	t_env				*env;
    unsigned int   		id;
	pthread_mutex_t 	*r_fork;
    pthread_mutex_t 	*l_fork;
}	t_philo;

// init.c 4
bool	init_env(char **argv, t_env *env, t_philo **philos, pthread_mutex_t	**forks);
bool    init_forks(pthread_mutex_t	**forks, unsigned int num_of_philo);
void    init_philos(t_philo **philos, t_env *env, pthread_mutex_t *forks);
unsigned int	get_time(void);
void	log(unsigned int ph_nbr, char *str);

// parse_input.c 3
bool			parse_argv(t_env *env, char **argv);
bool			ph_atoi(const char *str, unsigned int *result);

#endif
