/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:26:25 by aklimchu          #+#    #+#             */
/*   Updated: 2024/10/16 14:33:57 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_funct(void *data)
{
	t_philo *philo;
	int		i;

	philo = (t_philo *)data;
	i = 0; // how do we know in which thread we are now?
	/* while (1) // philo death?
	{ */
		pthread_mutex_lock(&philo->fork_mutex[i]);
		printf("Taking the fork number %d\n", i);
		pthread_mutex_unlock(&philo->fork_mutex[i]);
	/* } */
	return (NULL);
}