/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 10:31:27 by ekulichk          #+#    #+#             */
/*   Updated: 2023/07/26 03:36:15 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

bool	parse_argv(t_env *env, char **argv)
{
	if (!ph_atoi(argv[1], &env->num_of_philo))
		return (false);
	if (!ph_atoi(argv[2], &env->time_to_die))
		return (false);
	if (!ph_atoi(argv[3], &env->time_to_eat))
		return (false);
	if (!ph_atoi(argv[4], &env->time_to_sleep))
		return (false);
	if (argv[5] != NULL)
	{
		if (!ph_atoi(argv[5], &env->num_must_eat))
			return (false);
	}
	else
		env->num_must_eat = 0;
	return (true);
}

static int	get_len(const char *str)
{
	int	len;

	len = 0;
	while (*str)
	{
		len++;
		str++;
	}
	return (len);
}

bool	ph_atoi(const char *str, unsigned int *result)
{
	int		i;
	long	temp_res;

	i = 0;
	temp_res = 0;
	if (get_len(str) > 10)
		return (false);
	while (str[i] >= '0' && str[i] <= '9')
	{
		temp_res = temp_res * 10 + str[i] - '0';
		i++;
	}
	if (temp_res > INT_MAX || temp_res < INT_MIN || temp_res == 0)
		return (false);
	*result = temp_res;
	return (true);
}

void	print_malloc_failed(void)
{
	printf("malloc failed\n");
	exit(1);
}
