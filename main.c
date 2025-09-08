/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwrzosek <kwrzosek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 14:20:48 by kwrzosek          #+#    #+#             */
/*   Updated: 2025/09/03 16:39:36 by kwrzosek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//	TODO:
// destroy all mutexes
// format output to correct format

int	main(int argc, char **argv)
{
	t_philo philo;
	t_sim_params sim;
	int	i;
	int	number_of_philo;

	
	i = 0;
	number_of_philo = atoi(argv[1]);
	if (argc != 6 && argc != 5)
		return (print_error(4));
	else
	{
		validate_args(argc, argv);
		init_sim(&sim, argc, argv);
		init_philos(&sim);
		init_forks(&sim);
		create_threads(&sim);
		return(0);
	}
	return (0);
}
