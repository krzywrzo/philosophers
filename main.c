/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwrzosek <kwrzosek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 14:20:48 by kwrzosek          #+#    #+#             */
/*   Updated: 2025/09/25 22:21:40 by kwrzosek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_sim_params	*sim;

	sim = malloc(sizeof(t_sim_params));
	if (argc != 6 && argc != 5)
		return (1);
	else
	{
		validate_args(argc, argv);
		init_sim(sim, argc, argv);
		init_philos(sim);
		init_forks(sim);
		create_threads(sim);
		end_simulation(sim);
		return (0);
	}
	return (0);
}
