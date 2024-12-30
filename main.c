/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:44:22 by aklimchu          #+#    #+#             */
/*   Updated: 2024/11/21 12:08:41 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_input(int argc, char **argv);

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (check_input(argc, argv) == 1)
		return (1);
	if (fill_struct(argc, argv, &philo) == 1)
		return (1);
	if (init_mutex(&philo) == 1)
		return (1);
	if (create_threads(&philo) == 1)
		return (1);
	free_all(&philo, NULL);
	return (0);
}

// checking the number of arguments and if values are numerical / not negative 
static int	check_input(int argc, char **argv)
{
	int		i;

	if (argc < 5 || argc > 6)
	{
		input_error_print();
		return (1);
	}
	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) < 0)
		{
			input_error_print();
			return (1);
		}
		i++;
	}
	if (ft_atoi(argv[1]) == 0 || (argv[5] && ft_atoi(argv[5]) == 0))
		return (1);
	return (0);
}
