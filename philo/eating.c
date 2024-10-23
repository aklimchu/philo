/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:20:00 by aklimchu          #+#    #+#             */
/*   Updated: 2024/10/22 15:07:42 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	lock_first_fork(t_philo *philo, t_cur cur);

static int	lock_second_fork_and_eat(t_philo *philo, t_cur cur);

int	eating(t_philo *philo, t_cur cur)
{
	if (lock_first_fork(philo, cur) == 1)
		return (1);

	if (lock_second_fork_and_eat(philo, cur) == 1)
		return (1);

	philo->eaten_times[cur.philo_seat - 1]++; // or in the begining of the meal?

	pthread_mutex_lock(&philo->printf_mutex);
	printf("Philosopher %d has eaten %d times\n", cur.philo_seat, philo->eaten_times[cur.philo_seat - 1]);
	pthread_mutex_unlock(&philo->printf_mutex);
	
	pthread_mutex_unlock(&philo->fork_mutex[cur.fork_1 - 1]); // unlocking the first fork
	pthread_mutex_unlock(&philo->fork_mutex[cur.fork_2 - 1]); // unlocking the second fork
	return (0);
}

static int	lock_first_fork(t_philo *philo, t_cur cur)
{
	uint64_t			timestamp;
	struct		timeval	tv;
	
	if (check_flags(philo) == 1)
		return (1);
	
	if (philo->philo_num != 1)
	{
		pthread_mutex_lock(&philo->state_mutex[cur.philo_seat - 1]);
		philo->state[cur.philo_seat - 1] = EATING;
		pthread_mutex_unlock(&philo->state_mutex[cur.philo_seat - 1]);
	}

	pthread_mutex_lock(&philo->fork_mutex[cur.fork_1 - 1]); // locking the first fork

	gettimeofday(&tv, NULL);
	timestamp = (uint64_t)tv.tv_sec * 1000 + tv.tv_usec /1000 - philo->start_time;

	pthread_mutex_lock(&philo->printf_mutex);
	printf("%lu: Philo %d taking the fork number %d\n", timestamp, cur.philo_seat, cur.fork_1); // first fork - print
	pthread_mutex_unlock(&philo->printf_mutex);

	if (philo->philo_num == 1)
	{
		while (check_flags(philo) == 0)
		{
			ft_usleep(2);
		}
		return (1);
	}
	return (0);
}

static int	lock_second_fork_and_eat(t_philo *philo, t_cur cur)
{
	uint64_t			timestamp;
	struct		timeval	tv;
	uint64_t		eating_time;
	
	pthread_mutex_lock(&philo->fork_mutex[cur.fork_2 - 1]); // locking the second fork		

	check_philo(philo);
	
	if (check_flags(philo) == 1)
	{
		pthread_mutex_unlock(&philo->fork_mutex[cur.fork_1 - 1]); // unlocking the first fork
		pthread_mutex_unlock(&philo->fork_mutex[cur.fork_2 - 1]); // unlocking the second fork
		return (1);
	}

	gettimeofday(&tv, NULL);
	timestamp = (uint64_t)tv.tv_sec * 1000 + tv.tv_usec /1000 - philo->start_time;
	
	pthread_mutex_lock(&philo->last_meal_mutex[cur.philo_seat - 1]);
	philo->last_meal[cur.philo_seat - 1] = timestamp;
	pthread_mutex_unlock(&philo->last_meal_mutex[cur.philo_seat - 1]);

	pthread_mutex_lock(&philo->printf_mutex);
	printf("%lu: Philo %d taking the fork number %d\n", timestamp, cur.philo_seat, cur.fork_2); // second fork - print
	printf("%lu: Philo %d is eating\n", timestamp, cur.philo_seat); // eating - print
	pthread_mutex_unlock(&philo->printf_mutex);
			
	eating_time = 0;
	while (check_flags(philo) == 0 && eating_time < philo->time_to_eat)
	{
		ft_usleep(2); // eating - waiting
		eating_time += 2;
	}
	if (eating_time < philo->time_to_eat)
	{
		pthread_mutex_unlock(&philo->fork_mutex[cur.fork_1 - 1]); // unlocking the first fork
		pthread_mutex_unlock(&philo->fork_mutex[cur.fork_2 - 1]); // unlocking the second fork
		return (1);
	}
	return (0);
}