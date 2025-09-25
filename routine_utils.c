/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwrzosek <kwrzosek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:38:06 by kwrzosek          #+#    #+#             */
/*   Updated: 2025/09/25 22:58:59 by kwrzosek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_msg(t_philo *ph, char *msg)
{
	int	stopped;

	pthread_mutex_lock(&ph->sim->print_mutex);
	// pthread_mutex_lock(&ph->sim->stop_mutex);
	stopped = ph->sim->stop;
	// pthread_mutex_unlock(&ph->sim->stop_mutex);
	if (!stopped)
		printf("%ld %d %s\n", get_elapsed_time(ph->sim->start_time),
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

int	should_continue(t_philo *ph)
{
	int	stop;
	int	meals;

	pthread_mutex_lock(&ph->sim->stop_mutex);
	stop = ph->sim->stop;
	pthread_mutex_unlock(&ph->sim->stop_mutex);
	if (stop)
		return (0);
	pthread_mutex_lock(&ph->state_mutex);
	meals = ph->meals_eaten;
	pthread_mutex_unlock(&ph->state_mutex);
	if (ph->sim->no_of_meals >= 0 && meals >= ph->sim->no_of_meals)
		return (0);
	return (1);
}

int	update_state(t_philo *ph)
{
	pthread_mutex_lock(&ph->state_mutex);
	ph->last_meal = time_in_ms();
	ph->meals_eaten++;
	pthread_mutex_unlock(&ph->state_mutex);
	if (print_msg(ph, "is eating"))
		return (1);
	ft_sleep(ph->sim->time_to_eat);
	return (0);
}

int	finish_cycle(t_philo *ph)
{
	if (print_msg(ph, "is sleeping"))
		return (1);
	ft_sleep(ph->sim->time_to_sleep);
	if (print_msg(ph, "is thinking"))
		return (1);
	return (0);
}
