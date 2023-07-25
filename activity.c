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

int thinking(t_philo *philo, unsigned long last_meal)
{
	print_log(get_time() - philo->env->start_time, philo, "\033[0;34mis thinking\033[0m");
	if (philo->id % 2 == 0)
	{
		if (check_if_dead(philo))
			return (EXIT_FAILURE);
		if (!take_fork(philo->l_fork, last_meal + philo->env->time_to_die))
		{
			time_to_die(philo);
			return (EXIT_FAILURE);
		}
		print_log(get_time() - philo->env->start_time, philo, "has taken a fork");
		if (check_if_dead(philo))
			return (EXIT_FAILURE);
		if (!take_fork(philo->r_fork, last_meal + philo->env->time_to_die))
		{
			time_to_die(philo);
			unlock_fork(philo->l_fork);
			return (EXIT_FAILURE);
		}
		print_log(get_time() - philo->env->start_time, philo, "has taken a fork");
	}
	else
	{
		if (check_if_dead(philo))
			return (EXIT_FAILURE);
		if (!take_fork(philo->r_fork, last_meal + philo->env->time_to_die))
		{
			time_to_die(philo);
			return (EXIT_FAILURE);
		}
		print_log(get_time() - philo->env->start_time, philo, "has taken a fork");
		if (check_if_dead(philo))
			return (EXIT_FAILURE);
		if (!take_fork(philo->l_fork, last_meal + philo->env->time_to_die))
		{
			time_to_die(philo);
			unlock_fork(philo->r_fork);
			return (EXIT_FAILURE);
		}
		print_log(get_time() - philo->env->start_time, philo, "has taken a fork");
	}
	return  (EXIT_SUCCESS);
}

int eating_2(t_philo *philo)
{
	unsigned long	eat_start;

	eat_start = get_time();
	while (get_time() - eat_start < philo->env->time_to_eat)
	{
		if (check_if_dead(philo))
			return (EXIT_FAILURE);
		if (get_time() - eat_start >= philo->env->time_to_die)
		{
			time_to_die(philo);
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
	eating_2(philo);
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

int sleeping(t_philo *philo, unsigned long last_meal)
{
	unsigned long	sleep_start;

	sleep_start = get_time();
	print_log(get_time() - philo->env->start_time, philo, "\033[30;1mis sleeping\033[0m");
	while (get_time() - sleep_start < philo->env->time_to_sleep)
	{
		if (check_if_dead(philo))
			return (EXIT_FAILURE);
		if (get_time() - last_meal >= philo->env->time_to_die)
		{
			time_to_die(philo);
			return (EXIT_FAILURE);
		}
		usleep(100);
	}
	return (EXIT_SUCCESS);
}
