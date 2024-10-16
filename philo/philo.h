/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:44:48 by aklimchu          #+#    #+#             */
/*   Updated: 2024/10/16 14:04:19 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h> // printf
#include <pthread.h> // threads and mutexes
#include <sys/time.h> // gettimeofday
#include <stdlib.h> // exit
#include <string.h> // memset

typedef struct	s_philo
{
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_to_eat;
	pthread_t		*tid;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	printf_mutex;
	int				*eat_count;
}				t_philo;

void input_error_print();
void fill_struct(int argc, char **argv, t_philo *philo);
int ft_atoi(const char *str);
int create_threads(t_philo *philo);
void join_threads(t_philo *philo);
void *philo_funct(void *data);
int init_mutex(t_philo *philo);
void destroy_mutex(t_philo *philo);

#endif /*PHILO_H*/