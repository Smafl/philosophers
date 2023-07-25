/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 15:26:23 by ekulichk          #+#    #+#             */
/*   Updated: 2023/07/25 00:12:50 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_PHILO_H
#define PHILO_PHILO_H

# include <pthread.h>
# include <stdbool.h>

typedef struct s_fork
{
	pthread_mutex_t mutex;
	bool            taken;
}   t_fork;

typedef struct s_environment
{
	// todo signed int
    unsigned int 	num_of_philo;
    unsigned int 	time_to_die;
    unsigned int 	time_to_eat;
    unsigned int 	time_to_sleep;
    unsigned int 	num_must_eat;
    unsigned long	start_time;
	bool			is_dead;
	pthread_mutex_t	print;
	pthread_mutex_t	dead;
}	t_env;

typedef struct s_philo
{
	t_env			*env;
	unsigned int    id;
	t_fork       	*r_fork;
    t_fork       	*l_fork;
}	t_philo;

//				philo.c
void			*routine(void *argv);
void			*lonely_routine(void *argv);

// 				init.c 4
bool			init_env(char **argv, t_env *env, t_philo **philos, t_fork **forks);
bool    		init_forks(t_fork **forks, unsigned int num_of_philo);
void    		init_philos(t_philo **philos, t_env *env, t_fork *forks);
bool			thread_creation(pthread_t **thread, t_env *env, t_philo *philos);

//				activity.c
int 			thinking(t_philo *philo, unsigned long last_meal);
int 			eating(t_philo *philo, unsigned int *num_of_meals, unsigned long *last_meal);
int				sleeping(t_philo *philo, unsigned long last_meal);

//				utils.c
unsigned int	get_time(void);
void			print_log(unsigned int time, t_philo *philo, char *str);
void			print_malloc_failed(void);

// 				parse_input.c
bool			parse_argv(t_env *env, char **argv);
bool			ph_atoi(const char *str, unsigned int *result);

//				free.c
void	join_threads(t_philo *philos, pthread_t *threads);
void	destroy_mutexes(t_philo *philos, pthread_mutex_t *forks);
void	free_philos(t_philo **philos);
void	free_all(t_philo **philos, pthread_t *threads, pthread_mutex_t *forks);

/*
// take one fork
  - lock mutex
  - check death (if dead, then unlock mutex)
  - print
// take one fork
  - lock mutex
  - check death (if dead, then unlock mutex)
  - print
// eat
  - check death (if dead, then unlock mutex)
  - print
  - while loop  with sleep
// unlock one fork
  - unlock fork
// unlock one fork
  - unlock fork
// sleep
  - check death (if dead, then unlock mutex)
  - print
  - while loop with sleep
// think while of smaller intervals of sleep so that u can check death even when u r sleeping
  - check death (if dead, then unlock mutex)
  - print
  - while loop with sleep (depends on some variable that you decide)
*/
#endif
