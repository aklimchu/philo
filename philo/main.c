/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:44:22 by aklimchu          #+#    #+#             */
/*   Updated: 2024/10/16 14:28:46 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_input(int argc, char **argv);

int	main(int argc, char **argv)
{
	t_philo	philo;
	
	check_input(argc, argv);
	fill_struct(argc, argv, &philo);
	if (init_mutex(&philo) == 1)
		return(/* free_and_exit */ 1);
	if (create_threads(&philo) == 1)
		return (/* free_and_exit */ 1);
	join_threads(&philo);
	destroy_mutex(&philo);
	return (0);
}

static void	check_input(int argc, char **argv)
{
	int		error;
	int		i;

	error = 0;
	if (argc < 5 || argc > 6)
		error = 1;
	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) < 0)
			error = 1;
		i++;
	}
	if (error == 1)
	{
		input_error_print();
		exit(1);
	}
	if (ft_atoi(argv[1]) == 0 || (argv[5] && ft_atoi(argv[5]) == 0))
	{
		printf("\n");
		exit(0);
	}
}
