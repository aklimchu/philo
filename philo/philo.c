/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:26:25 by aklimchu          #+#    #+#             */
/*   Updated: 2024/10/22 15:09:34 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_values(t_philo *philo, t_cur *cur);

static int	sleeping(t_philo *philo, t_cur cur, int i);

static void	thinking(t_philo *philo, t_cur cur);

void	*philo_funct(void *data)
{
	t_philo 		*philo;
	t_cur			cur;
	int				i;
	
	philo = (t_philo *)data;
	set_values(philo, &cur);
	if (philo->num_to_eat == -1)
		i = -3;
	else
		i = 0;
	while (/* i < philo->num_to_eat &&  */philo->die_flag == 0 && philo->eat_enough_flag == 0)
	{
		if (philo->state[cur.philo_seat_previous - 1] != EATING && philo->state[cur.philo_seat_next - 1] != EATING) // not working 100% of time
		{
			if (eating(philo, cur) == 1)
				break ;
			if (sleeping(philo, cur, i) == 1)	
				break ;		
			thinking(philo, cur);
			if (philo->num_to_eat != -1)
				i++;
			/* if (i == philo->num_to_eat)
				break ; */
		}
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
		cur->philo_seat_next = cur->fork_2 + 1;
}

static int	sleeping(t_philo *philo, t_cur cur, int i)
{
	
	uint64_t		timestamp;
	struct timeval	tv;
	uint64_t		sleeping_time;
	
	sleeping_time = 0;
	if (philo->die_flag == 0 && philo->eat_enough_flag == 0)
	{
		philo->state[cur.philo_seat - 1] = SLEEPING;
	
		if (i + 1 == philo->num_to_eat)
		{
			check_philo(philo);
			if (philo->eat_enough_flag == 1 || philo->die_flag == 1)
				return (1);
		}
		gettimeofday(&tv, NULL);
		timestamp = (uint64_t)tv.tv_sec * 1000 + tv.tv_usec /1000 - philo->start_time;

		pthread_mutex_lock(&philo->printf_mutex);
		printf("%lu: Philo %d is sleeping\n", timestamp, cur.philo_seat); // sleeping - print
		pthread_mutex_unlock(&philo->printf_mutex);
	}
	while (philo->die_flag == 0 && philo->eat_enough_flag == 0 && sleeping_time < philo->time_to_sleep)
	{
		ft_usleep(2); // sleeping - waiting
		sleeping_time += 2;
	}
	if (sleeping_time < philo->time_to_sleep)
		return (1);
	return (0);
}

static void	thinking(t_philo *philo, t_cur cur)
{
	uint64_t				timestamp;
	struct timeval	tv;

	if (philo->die_flag == 0 && philo->eat_enough_flag == 0)
	{
		philo->state[cur.philo_seat - 1] = THINKING;
		gettimeofday(&tv, NULL);
		timestamp = (uint64_t)tv.tv_sec * 1000 + tv.tv_usec / 1000 - philo->start_time;
		pthread_mutex_lock(&philo->printf_mutex);
		printf("%lu: Philo %d is thinking\n", timestamp, cur.philo_seat); // thinking - print
		pthread_mutex_unlock(&philo->printf_mutex);
	}
}
