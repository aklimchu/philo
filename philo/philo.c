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
	int			philo_seat_previous;
	int			philo_seat_next;
	long int	time;
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
	
	
	while (/* i < philo->num_to_eat */ philo->die_flag == 0 && philo->eat_enough_flag == 0)
	{
		//---------------------------------eating-----------------------------
		if (philo->die_flag == 0 && philo->eat_enough_flag == 0 && \
			philo->state[philo_seat_previous - 1] != EATING && philo->state[philo_seat_next - 1] != EATING)
		{
			pthread_mutex_lock(&philo->eating_mutex); // locking the eating mutex
			
			philo->state[philo_seat - 1] = EATING;
			
			pthread_mutex_lock(&philo->fork_mutex[fork_1 - 1]); // locking the first fork

			gettimeofday(&tv, NULL);
			time = tv.tv_usec / 1000 - philo->start_ms;

			pthread_mutex_lock(&philo->printf_mutex);
			printf("%ld: Philo %d taking the fork number %d\n", time, philo_seat, fork_1); // first fork - print
			pthread_mutex_unlock(&philo->printf_mutex);
		
			pthread_mutex_lock(&philo->fork_mutex[fork_2 - 1]); // locking the second fork

			gettimeofday(&tv, NULL);
			time = tv.tv_usec / 1000 - philo->start_ms;
			
			pthread_mutex_lock(&philo->printf_mutex);
			printf("%ld: Philo %d taking the fork number %d\n", time, philo_seat, fork_2); // second fork - print
			pthread_mutex_unlock(&philo->printf_mutex);

			gettimeofday(&tv, NULL);
			time = tv.tv_usec / 1000 - philo->start_ms;

			pthread_mutex_lock(&philo->printf_mutex);
			printf("%ld: Philo %d is eating\n", time, philo_seat); // eating - print
			pthread_mutex_unlock(&philo->printf_mutex);

			usleep(philo->time_to_eat * 1000);// eating - waiting
			
			philo->eaten_times[philo_seat - 1]++;

			pthread_mutex_lock(&philo->printf_mutex);
			printf("Philosopher %d has eaten %d times\n", philo_seat, philo->eaten_times[philo_seat - 1]);
			pthread_mutex_unlock(&philo->printf_mutex);
			
			//check_times_eaten(philo);
			
			pthread_mutex_unlock(&philo->fork_mutex[fork_1 - 1]); // unlocking the first fork
		
			pthread_mutex_unlock(&philo->fork_mutex[fork_2 - 1]); // unlocking the second fork
			
			pthread_mutex_unlock(&philo->eating_mutex); // unlocking the eating mutex


			//-------------------------------sleeping-----------------------------
			long int sleeping_time = 0;
			if (philo->die_flag == 0 && philo->eat_enough_flag == 0)
			{
				philo->state[philo_seat - 1] = SLEEPING;
			
				gettimeofday(&tv, NULL);
				time = tv.tv_usec / 1000 - philo->start_ms;
				pthread_mutex_lock(&philo->printf_mutex);
				printf("%ld: Philo %d is sleeping\n", time, philo_seat); // sleeping - print
				pthread_mutex_unlock(&philo->printf_mutex);
			}
			while (philo->die_flag == 0 && philo->eat_enough_flag == 0 && sleeping_time < philo->time_to_sleep)
			{
				sleeping_time = sleeping_time + 2;
				usleep(2 * 1000); // sleeping - waiting
			}
			//-------------------------------thinking-----------------------------
			if (philo->die_flag == 0 && philo->eat_enough_flag == 0)
			{
				philo->state[philo_seat - 1] = THINKING;
				gettimeofday(&tv, NULL);
				time = tv.tv_usec / 1000 - philo->start_ms;
				pthread_mutex_lock(&philo->printf_mutex);
				printf("%ld: Philo %d is thinking\n", time, philo_seat); // thinking - print
				pthread_mutex_unlock(&philo->printf_mutex);
			}
				// if (philo->num_to_eat != -1)
				// 	i++;
		}
	}
	return (NULL);
}