/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:26:25 by aklimchu          #+#    #+#             */
/*   Updated: 2024/11/21 08:49:22 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_values(t_philo *philo, t_cur *cur);
static int	sleeping(t_philo *philo, t_cur cur);
static int	thinking(t_philo *philo, t_cur cur);
static void	philo_processes(t_philo *philo, t_cur cur);

// the function will is called by every philosoher's thread
void	*philo_funct(void *data)
{
	t_philo		*philo;
	t_cur		cur;
	uint64_t	thinking_time;

	philo = (t_philo *)data;
	set_values(philo, &cur);
	thinking(philo, cur);
	ft_usleep(1);
	thinking_time = 0;
	if (cur.philo_seat % 2 == 0 || cur.philo_seat == philo->philo_num)
	{
		while (check_flags(philo) == 0 && \
			thinking_time < philo->time_to_eat / 2)
		{
			ft_usleep(5);
			thinking_time += 5;
		}
	}
	philo_processes(philo, cur);
	return (NULL);
}

// setting local values for philosopher's thread
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

// philosopher thinking (when not eating or sleeping)
static int	thinking(t_philo *philo, t_cur cur)
{
	uint64_t		timestamp;
	struct timeval	tv;

	pthread_mutex_lock(&philo->printf_mutex);
	gettimeofday(&tv, NULL);
	timestamp = (uint64_t)tv.tv_sec * 1000 + tv.tv_usec / 1000 - \
		philo->start_time;
	if (check_flags(philo) == 0)
		printf("%lu %d is thinking\n", timestamp, cur.philo_seat);
	pthread_mutex_unlock(&philo->printf_mutex);
	return (0);
}

// philosopher's routine, loop will continue
// until check_flags function has returned false
static void	philo_processes(t_philo *philo, t_cur cur)
{
	while (check_flags(philo) == 0)
	{
		if (eating(philo, cur) == 1)
			break ;
		if (sleeping(philo, cur) == 1)
			break ;
		if (thinking(philo, cur) == 1)
			break ;
	}
}

// philosopher sleeping until his sleeping time has finished or
// until check_flags function has returned false
static int	sleeping(t_philo *philo, t_cur cur)
{
	uint64_t		time;
	struct timeval	tv;
	uint64_t		sleeping_time;

	sleeping_time = 0;
	if (check_eaten(philo, cur.philo_seat - 1) == philo->num_to_eat)
		check_philo(philo);
	pthread_mutex_lock(&philo->printf_mutex);
	gettimeofday(&tv, NULL);
	time = (uint64_t)tv.tv_sec * 1000 + tv.tv_usec / 1000 - \
		philo->start_time;
	if (check_flags(philo) == 0)
		printf("%lu %d is sleeping\n", time, cur.philo_seat);
	pthread_mutex_unlock(&philo->printf_mutex);
	while (check_flags(philo) == 0 && sleeping_time < philo->time_to_sleep)
	{
		ft_usleep(5);
		sleeping_time += 5;
	}
	if (sleeping_time < philo->time_to_sleep)
		return (1);
	return (0);
}
