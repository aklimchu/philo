/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 08:37:44 by aklimchu          #+#    #+#             */
/*   Updated: 2024/10/28 09:14:35 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_memory(t_philo *philo);

static void	free_memory_extra(t_philo *philo);

int	free_and_exit(t_philo *philo, int exit_code, char *error_message)
{
	join_threads(philo);
	destroy_mutex(philo);
	free_memory(philo);
	free_memory_extra(philo);
	if (error_message)
		printf("%s\n", error_message);
	exit(exit_code);
}

static void	free_memory(t_philo *philo)
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

static void	free_memory_extra(t_philo *philo)
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
