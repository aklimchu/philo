/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:22:19 by aklimchu          #+#    #+#             */
/*   Updated: 2024/10/22 14:39:11 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_philo *philo)
{
	int				i;
	int				error;
	struct timeval	tv;
	
	gettimeofday(&tv, NULL);
	philo->start_time = (uint64_t)tv.tv_sec * 1000 + tv.tv_usec / 1000;
	printf("Start time: %lu\n", philo->start_time);
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
	while (philo->eat_enough_flag == 0 && philo->die_flag == 0)
	{
		check_philo(philo);
		ft_usleep(2);
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

void	check_philo(t_philo *philo)
{
	int				i;
	int				philo_full;
	struct timeval	tv;
	uint64_t		timestamp;

	philo_full = 0;
	i = 0;
	while (i < philo->philo_num)
	{
		if (philo->num_to_eat != -1 && philo->eaten_times[i] >= philo->num_to_eat)
			philo_full++;
		gettimeofday(&tv, NULL);
		timestamp = (uint64_t)tv.tv_sec * 1000 + tv.tv_usec / 1000 - philo->start_time;
		if (timestamp - philo->last_meal[i] >= philo->time_to_die)
		{
			philo->die_flag = 1;
			pthread_mutex_lock(&philo->printf_mutex);
			printf("%lu: Philo %d died\n", timestamp, i + 1);
			pthread_mutex_unlock(&philo->printf_mutex);
			return ;
		}
		if (philo_full == philo->philo_num)
		{
			printf("everyone has eaten\n");
			philo->eat_enough_flag = 1;
			return ;
		}
		else
			i++;
	}
}

void	ft_usleep(uint64_t time_to_sleep)
{
	uint64_t		time_before;
	uint64_t		time_after;
	struct timeval	tv;
	
	gettimeofday(&tv, NULL);
	time_before = (uint64_t)tv.tv_sec * 1000 + tv.tv_usec / 1000;
	time_after = time_before;
	while (time_after - time_before < time_to_sleep)
	{
		usleep(500);
		gettimeofday(&tv, NULL);
		time_after = (uint64_t)tv.tv_sec * 1000 + tv.tv_usec / 1000;
	}
}