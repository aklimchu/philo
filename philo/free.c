// 42 header

#include "philo.h"

static void	free_memory(t_philo *philo);

static void	free_memory_extra(t_philo *philo);

int	free_and_exit(t_philo *philo, int exit_code, char *error_message)
{
	join_threads(philo);
	destroy_mutex(philo);
	free_memory(philo); // last? array of mutexes and threads
	free_memory_extra(philo); // last? array of mutexes and threads
	if (error_message)
		printf("%s\n", error_message);
	exit(exit_code);
}

static void	free_memory(t_philo *philo)
{
	if (philo->fork_mutex)
	{
		free(philo->fork_mutex);
		philo->fork_mutex = NULL;
	}
	if (philo->state_mutex)
	{
		free(philo->state_mutex);
		philo->state_mutex = NULL;
	}
	if (philo->last_meal_mutex)
	{
		free(philo->last_meal_mutex);
		philo->last_meal_mutex = NULL;
	}
	if (philo->eaten_times_mutex)
	{
		free(philo->eaten_times_mutex);
		philo->eaten_times_mutex = NULL;
	}
	if (philo->state)
	{
		free(philo->state);
		philo->state = NULL;
	}
	if (philo->eaten_times)
	{
		free(philo->eaten_times);
		philo->eaten_times = NULL;
	}
}

static void	free_memory_extra(t_philo *philo)
{
	if (philo->last_meal)
	{
		free(philo->last_meal);
		philo->last_meal = NULL;
	}
	if (philo->tid)
	{
		free(philo->tid);
		philo->tid = NULL;
	}
}