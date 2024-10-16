/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:24:38 by aklimchu          #+#    #+#             */
/*   Updated: 2024/10/16 14:33:02 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static const char	*white_spaces_and_exit(const char *str);

void	fill_struct(int argc, char **argv, t_philo *philo)
{
	philo->philo_num = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->num_to_eat = ft_atoi(argv[5]);
	else
		philo->num_to_eat = -1;
	philo->eat_count = (int *)malloc(philo->philo_num * sizeof(int));
	if (philo->eat_count == NULL)
	{
		perror("malloc() failed");
		exit (1);
	}
	memset(philo->eat_count, 0, philo->philo_num * sizeof(int));
}

void	input_error_print()
{
	printf("Correct input format:\n./philo number_of_philosophers time_to_die");
	printf("time_to_eat time_to_sleep\n[number_of_times_each_philosopher_must_eat].\n");
	printf("Values can't be negative and they have to be numbers.\n");
}

int	ft_atoi(const char *str)
{
	int			res;
	int			neg;
	long int	checkl;

	res = 0;
	neg = 1;
	checkl = 0;
	str = white_spaces_and_exit(str);
	if (*str == 45)
	{
		neg = neg * (-1);
		str++;
	}
	while (*str > 47 && *str < 58)
	{
		checkl = checkl * 10 + (*str - '0');
		if (checkl < 0 && neg == 1)
			return (-1);
		if (checkl < 0 && neg == -1)
			return (0);
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res * neg);
}

static const char	*white_spaces_and_exit(const char *str)
{
	int		start;
	int		i;
	
	start = 0;
	i = 0;
	while (str[i] == 32 || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == 43)
		i++;
	start = i;
	if (str[i] == 45)
		i++;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
		{
			input_error_print();
			exit(1);
		}
		i++;
	}
	return (&str[start]);
}