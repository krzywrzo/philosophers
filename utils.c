/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwrzosek <kwrzosek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 15:11:43 by kwrzosek          #+#    #+#             */
/*   Updated: 2025/09/07 18:21:31 by kwrzosek         ###   ########.fr       */
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
int	is_dead (t_philo *ph)
{
	if (ph->last_meal > ph->sim->time_to_die)
	{
		pthread_mutex_lock(&ph->sim->print_mutex);
		printf("ms: %ld id: %d is DEAD\n", get_elapsed_time(ph->sim->start_time), ph->id_philo);
		pthread_mutex_unlock(&ph->sim->print_mutex);
		return (1);
	}
	else
		return(0);
}
