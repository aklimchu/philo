/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_tools_extra.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 08:52:04 by aklimchu          #+#    #+#             */
/*   Updated: 2024/10/28 09:34:53 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// checking if any of the flags have been set to true
// (flags related to death of philosopher and
// to all philosophers having eaten enough)
int	check_flags(t_philo *philo)
{
	int		copy_die;
	int		copy_eat_all;

	pthread_mutex_lock(&philo->die_mutex);
	copy_die = philo->die_flag;
	pthread_mutex_unlock(&philo->die_mutex);
	if (copy_die == 1)
		return (1);
	pthread_mutex_lock(&philo->eat_all_mutex);
	copy_eat_all = philo->eat_enough_flag;
	pthread_mutex_unlock(&philo->eat_all_mutex);
	if (copy_eat_all == 1)
		return (1);
	else
		return (0);
}

// getting the timestamp of the last meal certain philosopher has eaten
uint64_t	check_last_meal(t_philo *philo, int count)
{
	uint64_t	res;

	pthread_mutex_lock(&philo->last_meal_mutex[count]);
	res = philo->last_meal[count];
	pthread_mutex_unlock(&philo->last_meal_mutex[count]);
	return (res);
}

// getting the number of meals certain philosopher has eaten
int	check_eaten(t_philo *philo, int count)
{
	int		res;

	pthread_mutex_lock(&philo->eaten_times_mutex[count]);
	res = philo->eaten_times[count];
	pthread_mutex_unlock(&philo->eaten_times_mutex[count]);
	return (res);
}

void	join_threads(t_philo *philo)
{
	int		i;

	i = 0;
	while (i < philo->threads_count)
	{
		pthread_join(philo->tid[i], NULL);
		i++;
	}
}
