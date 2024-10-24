// 42 header

#include "philo.h"

int	check_eating(t_philo *philo, int count)
{
	int	res;

	pthread_mutex_lock(&philo->state_mutex[count]);
	res = philo->state[count];
	pthread_mutex_unlock(&philo->state_mutex[count]);
	return(res);
}

int check_flags(t_philo *philo)
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

uint64_t check_last_meal(t_philo *philo, int count)
{
	uint64_t	res;

	pthread_mutex_lock(&philo->last_meal_mutex[count]);
	res = philo->last_meal[count];
	pthread_mutex_unlock(&philo->last_meal_mutex[count]);
	return(res);
}

int check_eaten_times(t_philo *philo, int count)
{
	int	res;

	pthread_mutex_lock(&philo->eaten_times_mutex[count]);
	res = philo->eaten_times[count];
	pthread_mutex_unlock(&philo->eaten_times_mutex[count]);
	return(res);
}