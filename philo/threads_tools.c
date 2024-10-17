/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:22:19 by aklimchu          #+#    #+#             */
/*   Updated: 2024/10/17 15:41:00 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_times_eaten(t_philo *philo);

int	create_threads(t_philo *philo)
{
	int				i;
	int				error;
	struct timeval	tv;
	
	philo->tid = (pthread_t *)malloc(philo->philo_num * sizeof(pthread_t));
	if (philo->tid == NULL)
	{
		perror("malloc() failed");
		exit (1);
	}
	i = 0;
	gettimeofday(&tv, NULL);
	philo->start_ms = tv.tv_usec / 1000;
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
	while (philo->num_to_eat != -1 && philo->eat_enough_flag == 0)
	{
		check_times_eaten(philo);
		//usleep(2000);
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

void	check_times_eaten(t_philo *philo)
{
	int		i;

	i = 0;
	while (i < philo->philo_num)
	{
		if (philo->eaten_times[i] < philo->num_to_eat)
			return ;
		i++;
	}
	philo->eat_enough_flag = 1;
}