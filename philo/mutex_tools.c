/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:42:32 by aklimchu          #+#    #+#             */
/*   Updated: 2024/10/16 14:03:57 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_philo *philo)
{
	int		i;
	
	philo->fork_mutex = (pthread_mutex_t *)malloc(philo->philo_num * sizeof(pthread_mutex_t));
	if (philo->fork_mutex == NULL)
	{
		perror("mutex_init() failed");
		return (1);
	}
	i = 0;
	while (i < philo->philo_num)
	{
		if (pthread_mutex_init(&philo->fork_mutex[i], NULL))
		{
			perror("mutex_init() failed");
			return (1);
		}
		i++;
	}
	return (0);
}

void destroy_mutex(t_philo *philo)
{
	int		i;

	i = 0;
	while (i < philo->philo_num)
	{
		pthread_mutex_destroy(&philo->fork_mutex[i]);
		i++;
	}
}