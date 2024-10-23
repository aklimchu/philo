/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:42:32 by aklimchu          #+#    #+#             */
/*   Updated: 2024/10/17 10:59:24 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_mutex_extra(t_philo *philo, int destroy_count);

static int	init_mutex_extra(t_philo *philo);

int	init_mutex(t_philo *philo)
{
	int		i;
	
	philo->fork_mutex = (pthread_mutex_t *)malloc(philo->philo_num * sizeof(pthread_mutex_t));
	if (philo->fork_mutex == NULL)
		return (free_and_exit(philo, 1, "malloc() failed"));
	i = 0;
	while (i < philo->philo_num)
	{
		if (pthread_mutex_init(&philo->fork_mutex[i], NULL))
			return (free_and_exit(philo, 1, "mutex_init() failed"));
		i++;
		philo->mutex_count++;
	}
	philo->state_mutex = (pthread_mutex_t *)malloc(philo->philo_num * sizeof(pthread_mutex_t));
	if (philo->state_mutex == NULL)
		return (free_and_exit(philo, 1, "malloc() failed"));
	i = 0;
	while (i < philo->philo_num)
	{
		if (pthread_mutex_init(&philo->state_mutex[i], NULL))
			return (free_and_exit(philo, 1, "mutex_init() failed"));
		i++;
		philo->mutex_count++;
	}
	philo->last_meal_mutex = (pthread_mutex_t *)malloc(philo->philo_num * sizeof(pthread_mutex_t));
	if (philo->last_meal_mutex == NULL)
		return (free_and_exit(philo, 1, "malloc() failed"));
	i = 0;
	while (i < philo->philo_num)
	{
		if (pthread_mutex_init(&philo->last_meal_mutex[i], NULL))
			return (free_and_exit(philo, 1, "mutex_init() failed"));
		i++;
		philo->mutex_count++;
	}
	if (init_mutex_extra(philo) == 1)
		return (free_and_exit(philo, 1, "mutex_init() failed"));
	return (0);
}

static int	init_mutex_extra(t_philo *philo)
{
	if (pthread_mutex_init(&philo->philo_count_mutex, NULL))
		return (1);
	philo->mutex_count++;
	if (pthread_mutex_init(&philo->printf_mutex, NULL))
		return (1);
	philo->mutex_count++;
	if (pthread_mutex_init(&philo->die_mutex, NULL))
		return (1);
	philo->mutex_count++;
	if (pthread_mutex_init(&philo->eat_all_mutex, NULL))
		return (1);
	philo->mutex_count++;
	return (0);
}

void	destroy_mutex(t_philo *philo)
{
	int		i;
	int		destroy_count;

	i = 0;
	destroy_count = 0;
	while (destroy_count < philo->mutex_count && i < philo->philo_num)
	{
		pthread_mutex_destroy(&philo->fork_mutex[i]);
		i++;
		destroy_count++;
	}
	i = 0;
	while (destroy_count < philo->mutex_count && i < philo->philo_num)
	{
		pthread_mutex_destroy(&philo->state_mutex[i]);
		i++;
		destroy_count++;
	}
	i = 0;
	while (destroy_count < philo->mutex_count && i < philo->philo_num)
	{
		pthread_mutex_destroy(&philo->last_meal_mutex[i]);
		i++;
		destroy_count++;
	}
	if (destroy_count < philo->mutex_count)
	{
		pthread_mutex_destroy(&philo->philo_count_mutex);
		destroy_count++;
	}
	if (destroy_count < philo->mutex_count)
	{
		pthread_mutex_destroy(&philo->printf_mutex);
		destroy_count++;
	}
	destroy_mutex_extra(philo, destroy_count);
}

static void	destroy_mutex_extra(t_philo *philo, int destroy_count)
{
	if (destroy_count < philo->mutex_count)
	{
		pthread_mutex_destroy(&philo->die_mutex);
		destroy_count++;
	}
	if (destroy_count < philo->mutex_count)
		pthread_mutex_destroy(&philo->eat_all_mutex);
}