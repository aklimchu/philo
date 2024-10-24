/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:44:22 by aklimchu          #+#    #+#             */
/*   Updated: 2024/10/24 10:19:59 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_input(int argc, char **argv);

int	main(int argc, char **argv)
{
	t_philo	philo;
	
	check_input(argc, argv);
	fill_struct(argc, argv, &philo);
	init_mutex(&philo);
	create_threads(&philo);
	free_and_exit(&philo, 0, NULL);
	return (0);
}

static void	check_input(int argc, char **argv)
{
	int		i;

	if (argc < 5 || argc > 6)
	{
		input_error_print();
		exit(1);
	}
	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) < 0)
		{
			input_error_print();
			exit(1);
		}
		i++;
	}
	if (ft_atoi(argv[1]) == 0 || (argv[5] && ft_atoi(argv[5]) == 0))
		exit(0);
}

