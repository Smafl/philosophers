/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 23:26:57 by ekulichk          #+#    #+#             */
/*   Updated: 2023/07/24 23:50:15 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void    unlock_fork(t_fork *fork)
{
//	pthread_mutex_lock(&fork->mutex);
	fork->taken = false;
	pthread_mutex_unlock(&fork->mutex);
}

bool    take_fork(t_fork *l_fork,unsigned int time_out)
{
	while (get_time() <= time_out)
	{
		pthread_mutex_lock(&l_fork->mutex);
		if (!l_fork->taken)
		{
			l_fork->taken = true;
//			pthread_mutex_unlock(&l_fork->mutex);
			return (true);
		}
		pthread_mutex_unlock(&l_fork->mutex);
		usleep(100);
	}
	return (false);
}

int thinking(t_philo *philo, unsigned long last_meal)
{
	print_log(get_time() - philo->env->start_time, philo, "\033[0;34mis thinking\033[0m");
	if (philo->id % 2 == 0)
	{
		if (!take_fork(philo->l_fork, last_meal + philo->env->time_to_die))
		{
			print_log(get_time() - philo->env->start_time, philo, "\033[0;31mdied\033[0m");
			pthread_mutex_lock(&philo->env->dead);
			philo->env->is_dead = true;
			pthread_mutex_unlock(&philo->env->dead);
			return (EXIT_FAILURE);
		}
		print_log(get_time() - philo->env->start_time, philo, "has taken a fork");
		if (!take_fork(philo->r_fork, last_meal + philo->env->time_to_die))
		{
			print_log(get_time() - philo->env->start_time, philo, "\033[0;31mdied\033[0m");
			pthread_mutex_lock(&philo->env->dead);
			philo->env->is_dead = true;
			pthread_mutex_unlock(&philo->env->dead);
			unlock_fork(philo->l_fork);
			return (EXIT_FAILURE);
		}
		print_log(get_time() - philo->env->start_time, philo, "has taken a fork");
	}
	else
	{

		if (!take_fork(philo->r_fork, last_meal + philo->env->time_to_die))
		{
			print_log(get_time() - philo->env->start_time, philo, "\033[0;31mdied\033[0m");
			pthread_mutex_lock(&philo->env->dead);
			philo->env->is_dead = true;
			pthread_mutex_unlock(&philo->env->dead);
			return (EXIT_FAILURE);
		}
		print_log(get_time() - philo->env->start_time, philo, "has taken a fork");
		if (!take_fork(philo->l_fork, last_meal + philo->env->time_to_die))
		{
			print_log(get_time() - philo->env->start_time, philo, "\033[0;31mdied\033[0m");
			pthread_mutex_lock(&philo->env->dead);
			philo->env->is_dead = true;
			pthread_mutex_unlock(&philo->env->dead);
			unlock_fork(philo->r_fork);
			return (EXIT_FAILURE);
		}
		print_log(get_time() - philo->env->start_time, philo, "has taken a fork");
	}
	return  (EXIT_SUCCESS);
}

int eating_2(t_philo *philo, unsigned long last_meal)
{
	unsigned long	sleep_start;

	(void)last_meal;
	sleep_start = get_time();
	while (get_time() - sleep_start < philo->env->time_to_eat)
	{
		pthread_mutex_lock(&philo->env->dead);
		if (philo->env->is_dead)
		{
			pthread_mutex_unlock(&philo->env->dead);
			return (EXIT_FAILURE);
		}
		pthread_mutex_unlock(&philo->env->dead);
		if (get_time() - sleep_start >= philo->env->time_to_die)
		{
			print_log(get_time() - philo->env->start_time, philo, "\033[0;31mdied\033[0m");
			pthread_mutex_lock(&philo->env->dead);
			philo->env->is_dead = true;
			pthread_mutex_unlock(&philo->env->dead);
			return (EXIT_FAILURE);
		}
		usleep(100);
	}
	return (EXIT_SUCCESS);
}

int eating(t_philo *philo, unsigned int *num_of_meals, unsigned long *last_meal)
{
	*last_meal = get_time();
	print_log(get_time() - philo->env->start_time, philo, "\033[0;32mis eating\033[0m");
	eating_2(philo, *last_meal);
	if (philo->env->num_must_eat != 0)
	{
		*num_of_meals += 1;
		if (*num_of_meals == philo->env->num_must_eat)
		{
			unlock_fork(philo->l_fork);
			unlock_fork(philo->r_fork);
			return (EXIT_FAILURE);
		}
	}
	unlock_fork(philo->l_fork);
	unlock_fork(philo->r_fork);
	return (EXIT_SUCCESS);
}

// todo
// doesn't work case ./philo 4 410 200 200 -- nobody should die

int sleeping(t_philo *philo, unsigned long last_meal)
{
	unsigned long	sleep_start;

	(void)last_meal;
	sleep_start = get_time();
	print_log(get_time() - philo->env->start_time, philo, "\033[30;1mis sleeping\033[0m");
	while (get_time() - sleep_start < philo->env->time_to_sleep)
	{
		pthread_mutex_lock(&philo->env->dead);
		if (philo->env->is_dead)
		{
			pthread_mutex_unlock(&philo->env->dead);
			return (EXIT_FAILURE);
		}
		pthread_mutex_unlock(&philo->env->dead);
		if (get_time() - sleep_start >= philo->env->time_to_die)
		{
			print_log(get_time() - philo->env->start_time, philo, "\033[0;31mdied\033[0m");
			pthread_mutex_lock(&philo->env->dead);
			philo->env->is_dead = true;
			pthread_mutex_unlock(&philo->env->dead);
			return (EXIT_FAILURE);
		}
		usleep(100);
	}
	return (EXIT_SUCCESS);
}
