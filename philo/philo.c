/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:26:25 by aklimchu          #+#    #+#             */
/*   Updated: 2024/10/17 15:40:29 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_funct(void *data)
{
	t_philo 	*philo;
	int			philo_seat;
	int			fork_1;
	int			fork_2;
	int			i;
	int			philo_seat_previous;
	int			philo_seat_next;
	long int	timestamp;
	struct timeval	tv;
	
	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->philo_count_mutex);
	philo->philo_count++;
	philo_seat = philo->philo_count;
	pthread_mutex_unlock(&philo->philo_count_mutex);
	if (philo_seat == 1)
		fork_1 = philo->philo_num;
	else
		fork_1 = philo_seat - 1;
	fork_2 = philo_seat;

	philo_seat_previous = fork_1;
	if (philo_seat == philo->philo_num)
		philo_seat_next = 1;
	else
		philo_seat_next = fork_2 + 1;
	if (philo->num_to_eat == -1)
		i = -3;
	else
		i = 0;
	while (i < philo->num_to_eat && philo->die_flag == 0 && philo->eat_enough_flag == 0)
	{
		//---------------------------------eating-----------------------------
		if (philo->die_flag == 0 && philo->eat_enough_flag == 0 && \
			philo->state[philo_seat_previous - 1] != EATING && philo->state[philo_seat_next - 1] != EATING)
		{

			if (philo->philo_num != 1)
				philo->state[philo_seat - 1] = EATING;
			pthread_mutex_lock(&philo->fork_mutex[fork_1 - 1]); // locking the first fork

			gettimeofday(&tv, NULL);
			timestamp = tv.tv_sec * 1000 + tv.tv_usec /1000 - philo->start_time;

			pthread_mutex_lock(&philo->printf_mutex);
			printf("%ld: Philo %d taking the fork number %d\n", timestamp, philo_seat, fork_1); // first fork - print
			pthread_mutex_unlock(&philo->printf_mutex);

			if (philo->philo_num == 1)
			{
				while (philo->die_flag == 0)
				{
					usleep(2000);
				}
				break ;
			}

			pthread_mutex_lock(&philo->fork_mutex[fork_2 - 1]); // locking the second fork
			

			gettimeofday(&tv, NULL);
			timestamp = tv.tv_sec * 1000 + tv.tv_usec /1000 - philo->start_time;
			
			pthread_mutex_lock(&philo->printf_mutex);
			printf("%ld: Philo %d taking the fork number %d\n", timestamp, philo_seat, fork_2); // second fork - print
			pthread_mutex_unlock(&philo->printf_mutex);

			gettimeofday(&tv, NULL);
			timestamp = tv.tv_sec * 1000 + tv.tv_usec /1000 - philo->start_time;

			pthread_mutex_lock(&philo->printf_mutex);
			printf("%ld: Philo %d is eating\n", timestamp, philo_seat); // eating - print
			pthread_mutex_unlock(&philo->printf_mutex);
			
			long eating_time;

			eating_time = 0;
			while (philo->die_flag == 0 && philo->eat_enough_flag == 0 && eating_time < philo->time_to_eat)
			{
				usleep(2 * 1000); // eating - waiting
				eating_time += 2;
			}
			if (eating_time < philo->time_to_eat)
			{
				pthread_mutex_unlock(&philo->fork_mutex[fork_1 - 1]); // unlocking the first fork
				pthread_mutex_unlock(&philo->fork_mutex[fork_2 - 1]); // unlocking the second fork
				break ;
			}

			philo->eaten_times[philo_seat - 1]++;

			pthread_mutex_lock(&philo->printf_mutex);
			printf("Philosopher %d has eaten %d times\n", philo_seat, philo->eaten_times[philo_seat - 1]);
			pthread_mutex_unlock(&philo->printf_mutex);
		
			pthread_mutex_unlock(&philo->fork_mutex[fork_1 - 1]); // unlocking the first fork
			pthread_mutex_unlock(&philo->fork_mutex[fork_2 - 1]); // unlocking the second fork
			

			//-------------------------------sleeping-----------------------------
			long int sleeping_time = 0;
			if (philo->die_flag == 0 && philo->eat_enough_flag == 0)
			{
				philo->state[philo_seat - 1] = SLEEPING;
			
				gettimeofday(&tv, NULL);
				timestamp = tv.tv_sec * 1000 + tv.tv_usec /1000 - philo->start_time;
				philo->last_meal[philo_seat - 1] = timestamp;

				if (i + 1 == philo->num_to_eat)
					break ;

				pthread_mutex_lock(&philo->printf_mutex);
				printf("%ld: Philo %d is sleeping\n", timestamp, philo_seat); // sleeping - print
				pthread_mutex_unlock(&philo->printf_mutex);
			}
			while (philo->die_flag == 0 && philo->eat_enough_flag == 0 && sleeping_time < philo->time_to_sleep)
			{
				usleep(2 * 1000); // sleeping - waiting
				sleeping_time += 2;
			}
			//-------------------------------thinking-----------------------------
			if (philo->die_flag == 0 && philo->eat_enough_flag == 0)
			{
				philo->state[philo_seat - 1] = THINKING;
				gettimeofday(&tv, NULL);
				timestamp = tv.tv_sec * 1000 + tv.tv_usec /1000 - philo->start_time;
				pthread_mutex_lock(&philo->printf_mutex);
				printf("%ld: Philo %d is thinking\n", timestamp, philo_seat); // thinking - print
				pthread_mutex_unlock(&philo->printf_mutex);
			}
			if (philo->num_to_eat != -1)
				i++;
		}
	}
	return (NULL);
}
