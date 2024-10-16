/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:22:19 by aklimchu          #+#    #+#             */
/*   Updated: 2024/10/16 13:59:22 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_philo *philo)
{
	int		i;
	int		error;
	
	philo->tid = (pthread_t *)malloc(philo->philo_num * sizeof(pthread_t));
	if (philo->tid == NULL)
	{
		perror("malloc() failed");
		exit (1);
	}
	i = 0;
	while (i < philo->philo_num)
	{
		error = pthread_create(&(philo->tid[i]), NULL, &philo_funct, philo);
		if (error != 0)
		{
			printf("\nThread can't be created : [%s]", strerror(error));
			return (1);
		}
		i++;
	}
	return (0);
}

void	join_threads(t_philo *philo)
{
	int		i;

	i = 0;
	while (i < philo->philo_num)
	{
		pthread_join(philo->tid[i], NULL);
		i++;
	}
}