/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwrzosek <kwrzosek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 15:11:43 by kwrzosek          #+#    #+#             */
/*   Updated: 2025/09/23 14:39:32 by kwrzosek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(int flag)	// FIXME: add proper error flags 
{
	printf("%d", flag);
	return(write(STDERR_FILENO, "Error", 5));
}

int	validate_args(int argc, char **argv)
{
	int	i;

	i = 2;
	if (atoi(argv[1]) < 1)
		return(print_error(0));
	while (i < argc)
	{
		if (atoi(argv[i]) <= 0)
			return (print_error(1));
		i++;
	}
	return (0);
}
long	get_elapsed_time(long start_time)
{
	struct timeval	tv;
	long			ms;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (ms - start_time);
}

long	time_in_ms()
{
	long	ms;
	struct timeval tv;

	gettimeofday(&tv, NULL);
	ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (ms);
}
void	print_sim_params(t_sim_params *sim)
{
	int	i;

	if (!sim)
		return ;
	printf("=== Simulation Parameters ===\n");
	printf("no_of_philo: %d\n", sim->no_of_philo);
	printf("time_to_die: %d\n", sim->time_to_die);
	printf("time_to_eat: %d\n", sim->time_to_eat);
	printf("time_to_sleep: %d\n", sim->time_to_sleep);
	printf("no_of_meals: %d\n", sim->no_of_meals);
	printf("start_time: %ld\n", sim->start_time);
	printf("stop flag: %d\n", sim->stop);
	printf("Threads ptr: %p\n", (void *)sim->threads);
	printf("Forks ptr: %p\n", (void *)sim->forks);
	printf("Philos ptr: %p\n", (void *)sim->philos);
	i = 0;
	while (i < sim->no_of_philo)
	{
		// printf("Philo[%d] addr: %p\n", i, (void *)&sim->philos[i]);
		i++;
	}
	printf("=============================\n");
}
