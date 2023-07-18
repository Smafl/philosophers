/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 15:26:23 by ekulichk          #+#    #+#             */
/*   Updated: 2023/07/09 19:41:33 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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
//	pthread_mutex_t	print_log_mutex;
}	t_env;

typedef struct s_philo
{
	t_env				*env;
    unsigned int   		id;
	pthread_mutex_t 	*r_fork;
    pthread_mutex_t 	*l_fork;
}	t_philo;
//				philo.c
void			*routine(void *argv);

// 				init.c 4
bool			init_env(char **argv, t_env *env, t_philo **philos, pthread_mutex_t	**forks);
bool    		init_forks(pthread_mutex_t	**forks, unsigned int num_of_philo);
void    		init_philos(t_philo **philos, t_env *env, pthread_mutex_t *forks);
bool			thread_creation(pthread_t **thread, t_env *env, t_philo *philos);

//				activity.c
int 			thinking(t_philo *philo, unsigned long last_meal);
int 			eating(t_philo *philo, unsigned int *num_of_meals);
int				sleeping(t_philo *philo, unsigned long last_meal);

//				utils.c
unsigned int	get_time(void);
void			print_log(unsigned int time, unsigned int ph_nbr, char *str);
void			print_malloc_failed(void);

// 				parse_input.c
bool			parse_argv(t_env *env, char **argv);
bool			ph_atoi(const char *str, unsigned int *result);

//				free.c
void	join_threads(t_philo *philos, pthread_t *threads);
void	destroy_mutexes(t_philo *philos, pthread_mutex_t *forks);
void	free_philos(t_philo **philos);
void	free_all(t_philo **philos, pthread_t *threads, pthread_mutex_t *forks);

#endif
