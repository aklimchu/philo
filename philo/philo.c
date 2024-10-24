/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:26:25 by aklimchu          #+#    #+#             */
/*   Updated: 2024/10/24 15:30:14 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_values(t_philo *philo, t_cur *cur);

static int	sleeping(t_philo *philo, t_cur cur);

static int	thinking(t_philo *philo, t_cur cur);

void	*philo_funct(void *data)
{
	t_philo 		*philo;
	t_cur			cur;
	
	philo = (t_philo *)data;
	set_values(philo, &cur);
	if (cur.philo_seat % 2 == 0 || cur.philo_seat == philo->philo_num)
		ft_usleep(philo->time_to_eat / 2);
	while (check_flags(philo) == 0)
	{
		if (1/* check_eating(philo, cur.philo_seat_previous - 1) != EATING *//* &&\
			check_eating(philo, cur.philo_seat_next - 1) != EATING &&\
			check_eating(philo, cur.philo_seat_previous - 1) != FIRST_FORK &&\
			check_eating(philo, cur.philo_seat_next - 1) != FIRST_FORK */)
		{
			if (eating(philo, cur) == 1)
				break ;
			if (sleeping(philo, cur) == 1)	
				break ;		
			if (thinking(philo, cur) == 1)
				break ;
		}
		//check_philo(philo);
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

	cur->philo_seat_previous = cur->fork_1;

	if (cur->philo_seat == philo->philo_num)
		cur->philo_seat_next = 1;
	else
		cur->philo_seat_next = cur->philo_seat + 1;
}

static int	sleeping(t_philo *philo, t_cur cur)
{
	
	uint64_t		timestamp;
	struct timeval	tv;
	uint64_t		sleeping_time;
	
	sleeping_time = 0;
	if (check_eaten_times(philo, cur.philo_seat - 1) == philo->num_to_eat)
		check_philo(philo);
	if (check_flags(philo) == 0)
	{
		pthread_mutex_lock(&philo->state_mutex[cur.philo_seat - 1]);
		philo->state[cur.philo_seat - 1] = SLEEPING;
		pthread_mutex_unlock(&philo->state_mutex[cur.philo_seat - 1]);
	
		//check_philo(philo);
		/* if (check_flags(philo) == 1)
			return (1); */
		
		pthread_mutex_lock(&philo->printf_mutex);
		gettimeofday(&tv, NULL);
		timestamp = (uint64_t)tv.tv_sec * 1000 + tv.tv_usec /1000 - philo->start_time;
		if (check_flags(philo) == 0)
			printf("%lu %d is sleeping\n", timestamp, cur.philo_seat); // sleeping - print
		pthread_mutex_unlock(&philo->printf_mutex);
	}
	while (check_flags(philo) == 0 && sleeping_time < philo->time_to_sleep)
	{
		ft_usleep(5); // sleeping - waiting
		sleeping_time += 5;
	}
	if (sleeping_time < philo->time_to_sleep)
		return (1);
	return (0);
}

static int	thinking(t_philo *philo, t_cur cur)
{
	uint64_t				timestamp;
	struct timeval	tv;

	if (check_flags(philo) == 0)
	{
		pthread_mutex_lock(&philo->state_mutex[cur.philo_seat - 1]);
		philo->state[cur.philo_seat - 1] = THINKING;
		pthread_mutex_unlock(&philo->state_mutex[cur.philo_seat - 1]);
		//check_philo(philo);
		/* if (check_flags(philo) == 1)
			return (1); */
		
		pthread_mutex_lock(&philo->printf_mutex);
		gettimeofday(&tv, NULL);
		timestamp = (uint64_t)tv.tv_sec * 1000 + tv.tv_usec / 1000 - philo->start_time;
		if (check_flags(philo) == 0)
			printf("%lu %d is thinking\n", timestamp, cur.philo_seat); // thinking - print
		pthread_mutex_unlock(&philo->printf_mutex);
	}
	return (0);
}
