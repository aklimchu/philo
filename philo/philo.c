/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:26:25 by aklimchu          #+#    #+#             */
/*   Updated: 2024/10/28 09:40:31 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_values(t_philo *philo, t_cur *cur);

static int	sleeping(t_philo *philo, t_cur cur);

static int	thinking(t_philo *philo, t_cur cur);

void	*philo_funct(void *data)
{
	t_philo	*philo;
	t_cur	cur;

	philo = (t_philo *)data;
	set_values(philo, &cur);
	if (cur.philo_seat % 2 == 0 || cur.philo_seat == philo->philo_num)
		ft_usleep(philo->time_to_eat / 2);
	while (check_flags(philo) == 0)
	{
		if (eating(philo, cur) == 1)
			break ;
		if (sleeping(philo, cur) == 1)
			break ;
		if (thinking(philo, cur) == 1)
			break ;
	}
	return (NULL);
}

static void	set_values(t_philo *philo, t_cur *cur)
{
	pthread_mutex_lock(&philo->philo_count_mutex);
	philo->philo_count++;
	cur->philo_seat = philo->philo_count;
	pthread_mutex_unlock(&philo->philo_count_mutex);
	if (cur->philo_seat == 1)
		cur->fork_1 = philo->philo_num;
	else
		cur->fork_1 = cur->philo_seat - 1;
	cur->fork_2 = cur->philo_seat;
}

static int	sleeping(t_philo *philo, t_cur cur)
{
	uint64_t		time;
	struct timeval	tv;
	uint64_t		sleeping_time;

	sleeping_time = 0;
	if (check_eaten(philo, cur.philo_seat - 1) == philo->num_to_eat)
		check_philo(philo);
	if (check_flags(philo) == 0)
	{
		pthread_mutex_lock(&philo->printf_mutex);
		gettimeofday(&tv, NULL);
		time = (uint64_t)tv.tv_sec * 1000 + tv.tv_usec / 1000 - \
			philo->start_time;
		if (check_flags(philo) == 0)
			printf("%lu %d is sleeping\n", time, cur.philo_seat);
		pthread_mutex_unlock(&philo->printf_mutex);
	}
	while (check_flags(philo) == 0 && sleeping_time < philo->time_to_sleep)
	{
		ft_usleep(5);
		sleeping_time += 5;
	}
	if (sleeping_time < philo->time_to_sleep)
		return (1);
	return (0);
}

static int	thinking(t_philo *philo, t_cur cur)
{
	uint64_t		timestamp;
	struct timeval	tv;

	if (check_flags(philo) == 0)
	{
		pthread_mutex_lock(&philo->printf_mutex);
		gettimeofday(&tv, NULL);
		timestamp = (uint64_t)tv.tv_sec * 1000 + tv.tv_usec / 1000 - \
			philo->start_time;
		if (check_flags(philo) == 0)
			printf("%lu %d is thinking\n", timestamp, cur.philo_seat);
		pthread_mutex_unlock(&philo->printf_mutex);
	}
	return (0);
}
