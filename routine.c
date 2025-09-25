/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwrzosek <kwrzosek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:01:05 by kwrzosek          #+#    #+#             */
/*   Updated: 2025/09/25 22:14:29 by kwrzosek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	if (ph->sim->no_of_philo == 1)
	{
		pthread_mutex_lock(&ph->sim->print_mutex);
		printf("%ld %d has taken a fork\n",
			get_elapsed_time(ph->sim->start_time), ph->id_philo + 1);
		pthread_mutex_unlock(&ph->sim->print_mutex);
		ft_sleep(ph->sim->time_to_die);
		return (NULL);
	}
	while (should_continue(ph))
	{
		if (ph->id_philo % 2 == 0)
			even_fork(ph);
		else
			odd_fork(ph);
	}
	return (NULL);
}

int	even_fork(t_philo *ph)
{
	return (handle_forks(ph, ph->left_fork, ph->right_fork));
}

int	odd_fork(t_philo *ph)
{
	return (handle_forks(ph, ph->right_fork, ph->left_fork));
}

void	*monitor_routine(void *arg)
{
	t_sim_params	*sim;
	int				i;

	sim = (t_sim_params *)arg;
	while (1)
	{
		i = -1;
		while (++i < sim->no_of_philo)
			if (check_death(sim, &sim->philos[i]))
				return (NULL);
		if (check_full(sim))
			return (NULL);
		ft_sleep(1);
		pthread_mutex_lock(&sim->stop_mutex);
		if (sim->stop)
		{
			pthread_mutex_unlock(&sim->stop_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&sim->stop_mutex);
	}
}

void	end_simulation(t_sim_params *sim)
{
	int	i;

	i = 0;
	pthread_join(sim->monitor, NULL);
	while (i < sim->no_of_philo)
	{
		pthread_join(sim->threads[i], NULL);
		i++;
	}
	i = 0;
	while (i < sim->no_of_philo)
	{
		pthread_mutex_destroy(&sim->forks[i]);
		pthread_mutex_destroy(&sim->philos[i].state_mutex);
		i++;
	}
	pthread_mutex_destroy(&sim->stop_mutex);
	pthread_mutex_destroy(&sim->print_mutex);
	free(sim->philos);
	free(sim->forks);
	free(sim->threads);
	free(sim);
}
