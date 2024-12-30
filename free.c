/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 08:37:44 by aklimchu          #+#    #+#             */
/*   Updated: 2024/11/21 09:20:20 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_mutexes(t_philo *philo);
static void	free_rest_of_memory(t_philo *philo);

int	free_all(t_philo *philo, char *error_message)
{
	join_threads(philo);
	destroy_mutex(philo);
	free_mutexes(philo);
	free_rest_of_memory(philo);
	if (error_message)
		printf("%s\n", error_message);
	return (1);
}

static void	free_mutexes(t_philo *philo)
{
	if (philo->fork_mutex)
	{
		free(philo->fork_mutex);
		philo->fork_mutex = NULL;
	}
	if (philo->last_meal_mutex)
	{
		free(philo->last_meal_mutex);
		philo->last_meal_mutex = NULL;
	}
	if (philo->eaten_times_mutex)
	{
		free(philo->eaten_times_mutex);
		philo->eaten_times_mutex = NULL;
	}
	if (philo->eaten_times)
	{
		free(philo->eaten_times);
		philo->eaten_times = NULL;
	}
}

static void	free_rest_of_memory(t_philo *philo)
{
	if (philo->last_meal)
	{
		free(philo->last_meal);
		philo->last_meal = NULL;
	}
	if (philo->tid)
	{
		free(philo->tid);
		philo->tid = NULL;
	}
}
