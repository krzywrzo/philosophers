/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwrzosek <kwrzosek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:38:06 by kwrzosek          #+#    #+#             */
/*   Updated: 2025/09/23 15:54:11 by kwrzosek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_msg(t_philo *ph, char *msg)
{
	int	stopped;

	pthread_mutex_lock(&ph->sim->print_mutex);
	stopped = ph->sim->stop;
	if (!stopped)
		printf("%ld %d %s\n",
			get_elapsed_time(ph->sim->start_time),
			ph->id_philo + 1, msg);
	pthread_mutex_unlock(&ph->sim->print_mutex);
	return (stopped);
}
void	ft_sleep(long ms)
{
	long	current;
	long	finish;

	finish = time_in_ms() + ms;
	current = time_in_ms();
	while (current < finish)
		current = time_in_ms();
}