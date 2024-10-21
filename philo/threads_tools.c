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

void	check_philo(t_philo *philo);

int	create_threads(t_philo *philo)
{
	int				i;
	int				error;
	
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
	check_philo(philo);
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

void	check_philo(t_philo *philo)
{
	int				i;
	int				philo_full;
	struct timeval	tv;
	int				timestamp;

	i = 0;
	philo_full = 0;
	while (1)
	{
		if (philo->num_to_eat != -1 && philo->eaten_times[i] >= philo->num_to_eat)
			philo_full++;
		gettimeofday(&tv, NULL);
		timestamp = tv.tv_sec * 1000 + tv.tv_usec / 1000 - philo->start_time;
		if (philo->state[i] != EATING && \
			timestamp - philo->last_meal[i] >= philo->time_to_die)
		{
			philo->die_flag = 1;
			pthread_mutex_lock(&philo->printf_mutex);
			printf("%d: Philo %d died\n", timestamp, i + 1);
			pthread_mutex_unlock(&philo->printf_mutex);
			return ;
		}
		if (philo_full == philo->philo_num)
		{
			printf("everyone has eaten\n");
			philo->eat_enough_flag = 1;
			return ;
		}
		else if (i + 1 == philo->philo_num)
		{
			i = 0;
			philo_full = 0;
		}
		else
			i++;
		usleep(1000);
	}
}