/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwrzosek <kwrzosek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 22:12:29 by kwrzosek          #+#    #+#             */
/*   Updated: 2025/09/25 22:44:50 by kwrzosek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	handle_forks(t_philo *ph, int first, int second)
{
	if (pthread_mutex_lock(&ph->sim->forks[first]) != 0)
		return (1);
	if (print_msg(ph, "has taken a fork"))
		return (pthread_mutex_unlock(&ph->sim->forks[first]), 1);
	if (pthread_mutex_lock(&ph->sim->forks[second]) != 0)
		return (1);
	if (print_msg(ph, "has taken a fork"))
	{
		pthread_mutex_unlock(&ph->sim->forks[second]);
		pthread_mutex_unlock(&ph->sim->forks[first]);
		return (1);
	}
	if (update_state(ph))
	{
		pthread_mutex_unlock(&ph->sim->forks[second]);
		pthread_mutex_unlock(&ph->sim->forks[first]);
		return (1);
	}
	pthread_mutex_unlock(&ph->sim->forks[second]);
	pthread_mutex_unlock(&ph->sim->forks[first]);
	return (finish_cycle(ph));
}

int	check_death(t_sim_params *sim, t_philo *ph)
{
	long	now;
	int		dead;

	pthread_mutex_lock(&ph->state_mutex);
	now = time_in_ms();
	dead = (now - ph->last_meal > sim->time_to_die);
	pthread_mutex_unlock(&ph->state_mutex);
	if (!dead)
		return (0);
	pthread_mutex_lock(&sim->stop_mutex);
	if (!sim->stop)
	{
		sim->stop = 1;
		pthread_mutex_lock(&sim->print_mutex);
		printf("%ld %d died\n",
			get_elapsed_time(sim->start_time), ph->id_philo + 1);
		pthread_mutex_unlock(&sim->print_mutex);
	}
	pthread_mutex_unlock(&sim->stop_mutex);
	return (1);
}



// int	check_death(t_sim_params *sim, t_philo *ph)
// {
// 	pthread_mutex_lock(&ph->state_mutex);
// 	if (time_in_ms() - ph->last_meal > sim->time_to_die)
// 	{
// 		pthread_mutex_lock(&sim->stop_mutex);
// 		if (!sim->stop)
// 		{
// 			sim->stop = 1;
// 			pthread_mutex_lock(&sim->print_mutex);
// 			printf("%ld %d died\n", get_elapsed_time(sim->start_time),
// 				ph->id_philo + 1);
// 			pthread_mutex_unlock(&ph->state_mutex);
// 			pthread_mutex_unlock(&sim->print_mutex);
// 		}
// 		// pthread_mutex_unlock(&ph->state_mutex);
// 		pthread_mutex_unlock(&sim->stop_mutex);
// 		return (1);
// 	}
// 	pthread_mutex_unlock(&ph->state_mutex);
// 	return (0);
// }

int	check_full(t_sim_params *sim)
{
	int	i;
	int	full_count;

	full_count = 0;
	i = -1;
	while (++i < sim->no_of_philo)
	{
		pthread_mutex_lock(&sim->philos[i].state_mutex);
		if (sim->no_of_meals > 0
			&& sim->philos[i].meals_eaten >= sim->no_of_meals)
			full_count++;
		pthread_mutex_unlock(&sim->philos[i].state_mutex);
	}
	if (sim->no_of_meals > 0 && full_count == sim->no_of_philo)
	{
		pthread_mutex_lock(&sim->stop_mutex);
		sim->stop = 1;
		pthread_mutex_unlock(&sim->stop_mutex);
		return (1);
	}
	return (0);
}
