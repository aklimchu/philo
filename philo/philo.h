/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:44:48 by aklimchu          #+#    #+#             */
/*   Updated: 2024/10/17 14:22:17 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h> // printf
#include <pthread.h> // threads and mutexes
#include <sys/time.h> // gettimeofday
#include <stdlib.h> // exit
#include <string.h> // memset
#include <unistd.h> // usleep

enum state 
{
    EATING = 0, // philosopher is EATING
    SLEEPING = 1, // philosopher is SLEEPING
	THINKING = 2, // philosopher is THINKING
};

typedef struct	s_philo
{
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_to_eat;
	long int		start_ms;
	pthread_t		*tid;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	printf_mutex;
	pthread_mutex_t	eating_mutex;
	pthread_mutex_t	philo_count_mutex;
	int				philo_count;
	int				*state;
	int				*eaten_times;
	int				die_flag;
	int				eat_enough_flag;
}				t_philo;

void input_error_print();
void fill_struct(int argc, char **argv, t_philo *philo);
int ft_atoi(const char *str);
int create_threads(t_philo *philo);
void join_threads(t_philo *philo);
void *philo_funct(void *data);
int init_mutex(t_philo *philo);
void destroy_mutex(t_philo *philo);
void check_times_eaten(t_philo *philo);

#endif /*PHILO_H*/