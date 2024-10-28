/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:44:48 by aklimchu          #+#    #+#             */
/*   Updated: 2024/10/28 09:35:03 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> // printf
# include <pthread.h> // threads and mutexes
# include <sys/time.h> // gettimeofday
# include <stdlib.h> // exit
# include <string.h> // memset
# include <unistd.h> // usleep
# include <stdint.h> // uint64_t

typedef struct s_philo
{
	int				philo_num;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				num_to_eat;
	uint64_t		start_time;
	pthread_t		*tid;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	*last_meal_mutex;
	pthread_mutex_t	*eaten_times_mutex;
	pthread_mutex_t	printf_mutex;
	pthread_mutex_t	philo_count_mutex;
	pthread_mutex_t	die_mutex;
	pthread_mutex_t	eat_all_mutex;
	int				mutex_count;
	int				threads_count;
	int				philo_count;
	int				*eaten_times;
	uint64_t		*last_meal;
	int				die_flag;
	int				die_message_printed;
	int				eat_enough_flag;
}				t_philo;

typedef struct s_cur
{
	int			philo_seat;
	int			fork_1;
	int			fork_2;
}				t_cur;

void		input_error_print(void);
int			fill_struct(int argc, char **argv, t_philo *philo);
int			ft_atoi(const char *str);
int			create_threads(t_philo *philo);
void		join_threads(t_philo *philo);
void		*philo_funct(void *data);
int			init_mutex(t_philo *philo);
void		destroy_mutex(t_philo *philo);
int			eating(t_philo *philo, t_cur cur);
void		check_philo(t_philo *philo);
int			free_and_exit(t_philo *philo, int exit_code, char *error_message);
void		ft_usleep(uint64_t time_to_sleep);
int			check_flags(t_philo *philo);
uint64_t	check_last_meal(t_philo *philo, int count);
int			check_eaten(t_philo *philo, int count);

#endif /*PHILO_H*/