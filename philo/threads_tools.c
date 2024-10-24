/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:22:19 by aklimchu          #+#    #+#             */
/*   Updated: 2024/10/24 15:12:15 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_philo *philo)
{
	struct timeval	tv;
	
	gettimeofday(&tv, NULL);
	philo->start_time = (uint64_t)tv.tv_sec * 1000 + tv.tv_usec / 1000;
	//printf("Start time: %lu\n", philo->start_time);
	philo->tid = (pthread_t *)malloc(philo->philo_num * sizeof(pthread_t));
	if (philo->tid == NULL)
		return(free_and_exit(philo, 1, "malloc() failed"));
	
	while (philo->threads_count < philo->philo_num)
	{
		if (pthread_create(&(philo->tid[philo->threads_count]), \
			NULL, &philo_funct, philo))
			return(free_and_exit(philo, 1, "pthread_create() failed"));
		philo->threads_count++;
	}
	while (check_flags(philo) == 0)
	{
		check_philo(philo);
		ft_usleep(5);
	}
	return (0);
}

void	join_threads(t_philo *philo)
{
	int		i;

	i = 0;
	while (i < philo->threads_count)
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
		if (philo->num_to_eat != -1 && check_eaten_times(philo, i) >= philo->num_to_eat)
			philo_full++;
		gettimeofday(&tv, NULL);
		timestamp = (uint64_t)tv.tv_sec * 1000 + tv.tv_usec / 1000 - philo->start_time;
		if (timestamp - check_last_meal(philo, i) >= philo->time_to_die)
		{
			//printf("start time %lu, time to die %lu, timestamp - check_last_meal %lu\n", philo->start_time, philo->time_to_die, timestamp - check_last_meal(philo, i));
			pthread_mutex_lock(&philo->die_mutex);
			philo->die_flag = 1;
			pthread_mutex_unlock(&philo->die_mutex);
			
			pthread_mutex_lock(&philo->printf_mutex);
			gettimeofday(&tv, NULL);
			timestamp = (uint64_t)tv.tv_sec * 1000 + tv.tv_usec / 1000 - philo->start_time;
			if (philo->die_message_printed == 0)
			{
				printf("%lu %d died\n", timestamp, i + 1);
				philo->die_message_printed = 1;
			}
			pthread_mutex_unlock(&philo->printf_mutex);
			return ;
		}
		if (philo_full == philo->philo_num)
		{
			//printf("everyone has eaten\n");
			pthread_mutex_lock(&philo->eat_all_mutex);
			philo->eat_enough_flag = 1;
			pthread_mutex_unlock(&philo->eat_all_mutex);
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
