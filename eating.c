/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:20:00 by aklimchu          #+#    #+#             */
/*   Updated: 2024/11/21 09:47:30 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	lock_first_fork(t_philo *philo, t_cur cur);
static int	lock_second_fork_and_eat(t_philo *philo, t_cur cur);
static int	print_message_and_eat(t_philo *philo, t_cur cur);
static void	add_delay(t_philo *philo, t_cur cur);

// philosopher eating until his eating time has finished or
// until check_flags function has returned false
int	eating(t_philo *philo, t_cur cur)
{
	add_delay(philo, cur);
	if (lock_first_fork(philo, cur) == 1)
		return (1);
	if (lock_second_fork_and_eat(philo, cur) == 1)
		return (1);
	pthread_mutex_lock(&philo->eaten_times_mutex[cur.philo_seat - 1]);
	philo->eaten_times[cur.philo_seat - 1]++;
	pthread_mutex_unlock(&philo->eaten_times_mutex[cur.philo_seat - 1]);
	pthread_mutex_unlock(&philo->fork_mutex[cur.fork_1 - 1]);
	pthread_mutex_unlock(&philo->fork_mutex[cur.fork_2 - 1]);
	return (0);
}

// locking the first fork and printing a corresponding message
static int	lock_first_fork(t_philo *philo, t_cur cur)
{
	uint64_t		timestamp;
	struct timeval	tv;

	pthread_mutex_lock(&philo->fork_mutex[cur.fork_1 - 1]);
	pthread_mutex_lock(&philo->printf_mutex);
	gettimeofday(&tv, NULL);
	timestamp = (uint64_t)tv.tv_sec * 1000 + tv.tv_usec / 1000 - \
		philo->start_time;
	if (check_flags(philo) == 0)
		printf("%lu %d has taken a fork\n", timestamp, cur.philo_seat);
	pthread_mutex_unlock(&philo->printf_mutex);
	if (philo->philo_num == 1)
	{
		while (check_flags(philo) == 0)
			ft_usleep(5);
		pthread_mutex_unlock(&philo->fork_mutex[cur.fork_1 - 1]);
		return (1);
	}
	return (0);
}

// locking the second fork and updating the time of last meal
static int	lock_second_fork_and_eat(t_philo *philo, t_cur cur)
{
	uint64_t		timestamp;
	struct timeval	tv;

	pthread_mutex_lock(&philo->fork_mutex[cur.fork_2 - 1]);
	if (check_flags(philo) == 1)
	{
		pthread_mutex_unlock(&philo->fork_mutex[cur.fork_1 - 1]);
		pthread_mutex_unlock(&philo->fork_mutex[cur.fork_2 - 1]);
		return (1);
	}
	pthread_mutex_lock(&philo->last_meal_mutex[cur.philo_seat - 1]);
	gettimeofday(&tv, NULL);
	timestamp = (uint64_t)tv.tv_sec * 1000 + tv.tv_usec / 1000 - \
		philo->start_time;
	philo->last_meal[cur.philo_seat - 1] = timestamp;
	pthread_mutex_unlock(&philo->last_meal_mutex[cur.philo_seat - 1]);
	pthread_mutex_lock(&philo->printf_mutex);
	return (print_message_and_eat(philo, cur));
}

// printing a message about locking the second fork and starting the meal
static int	print_message_and_eat(t_philo *philo, t_cur cur)
{
	uint64_t		time;
	struct timeval	tv;
	uint64_t		eating_time;

	gettimeofday(&tv, NULL);
	time = (uint64_t)tv.tv_sec * 1000 + tv.tv_usec / 1000 - philo->start_time;
	if (check_flags(philo) == 0)
	{
		printf("%lu %d has taken a fork\n", time, cur.philo_seat);
		printf("%lu %d is eating\n", time, cur.philo_seat);
	}
	pthread_mutex_unlock(&philo->printf_mutex);
	eating_time = 0;
	while (check_flags(philo) == 0 && eating_time < philo->time_to_eat)
	{
		ft_usleep(5);
		eating_time += 5;
	}
	if (eating_time < philo->time_to_eat)
	{
		pthread_mutex_unlock(&philo->fork_mutex[cur.fork_1 - 1]);
		pthread_mutex_unlock(&philo->fork_mutex[cur.fork_2 - 1]);
		return (1);
	}
	return (0);
}

// adding a delay if philosopher is ready to eat again too soon
// after the previous meal
static void	add_delay(t_philo *philo, t_cur cur)
{
	struct timeval	tv;
	uint64_t		timestamp;
	uint64_t		delay_time;

	gettimeofday(&tv, NULL);
	timestamp = (uint64_t)tv.tv_sec * 1000 + tv.tv_usec / 1000 - \
		philo->start_time;
	if (philo->eaten_times[cur.philo_seat - 1] == 0)
		return ;
	if (timestamp - philo->last_meal[cur.philo_seat - 1] \
		< philo->time_to_die / 2)
	{
		delay_time = 0;
		while (check_flags(philo) == 0 && \
			delay_time < philo->time_to_die / 2 - \
			(timestamp - philo->last_meal[cur.philo_seat - 1]))
		{
			ft_usleep(5);
			delay_time += 5;
		}
	}
}
