/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 15:26:23 by ekulichk          #+#    #+#             */
/*   Updated: 2023/07/26 15:39:52 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	bool			taken;
}	t_fork;

typedef struct s_environment
{
	const unsigned int	num_of_philo;
	const unsigned int	time_to_die;
	const unsigned int	time_to_eat;
	const unsigned int	time_to_sleep;
	const unsigned int	num_must_eat;
	unsigned long		start_time;
	bool				stop_sim;
	bool				is_dead;
	pthread_mutex_t		print;
	pthread_mutex_t		dead;
}	t_env;

typedef struct s_philo
{
	t_env			*env;
	unsigned int	id;
	t_fork			*r_fork;
	t_fork			*l_fork;
}	t_philo;

//				philo.c
//				main()
void			*routine(void *argv);
void			*lonely_routine(void *argv);
unsigned int	get_time(void);

// 				init.c
bool			init_env(
					char **argv, t_env *env, t_philo **philos, t_fork **forks);
bool			env_mutex_init(t_env *env);
bool			init_forks(
					t_fork **forks,
					unsigned int num_of_philo, unsigned int *inited);
void			init_philos(t_philo **philos, t_env *env, t_fork *forks);
bool			thread_creation(
					pthread_t **threads, t_env *env, t_philo *philos);

//				activity.c
int				thinking(t_philo *philo, unsigned long last_meal);
int				eating(
					t_philo *philo,
					unsigned int *num_of_meals, unsigned long *last_meal);
int				sleeping(t_philo *philo, unsigned long last_meal);

//				utils.c
bool			take_fork(t_fork *fork, unsigned int time_out);
void			unlock_fork(t_fork *fork);
void			print_log(unsigned int time, t_philo *philo, char *str);
int				check_if_dead(t_philo *philo);
void			time_to_die(t_philo *philo);

// 				parse_input.c
bool			parse_argv(t_env *env, char **argv);
bool			ph_atoi(const char *str, const unsigned int *result);
void			print_malloc_failed(void);

//				free.c
void			join_threads(pthread_t *threads, unsigned int num_of_philo);
void			destroy_mutexes(
					t_philo *philos, t_fork *forks, unsigned int num_of_philo);
void			free_all(t_philo *philos, pthread_t *threads, t_fork *forks);

#endif
