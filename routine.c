/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwrzosek <kwrzosek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:01:05 by kwrzosek          #+#    #+#             */
/*   Updated: 2025/09/08 13:00:30 by kwrzosek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo)
{
	t_philo *ph;
	
	ph = philo;
	if (ph->sim->no_of_philo == 1)
	{
		pthread_mutex_lock(&ph->sim->print_mutex);
		printf("ms: %ld id: %d has taken fork\n", get_elapsed_time(ph->sim->start_time), ph->id_philo);
		printf("ms: %ld id: %d has DIED\n", get_elapsed_time(ph->sim->start_time), ph->id_philo);
		pthread_mutex_unlock(&ph->sim->print_mutex);
		end_simulation(ph);
	}
	while (ph->is_dead != 1 && ph->enough_eaten != 1)
	{
		if (ph->id_philo % 2 == 0)
			even_fork(ph);
		else
			odd_fork(ph);
	}
	return(NULL);
}

void	even_fork(t_philo *ph)
{
	pthread_mutex_lock(&ph->sim->forks[ph->left_fork]);
	pthread_mutex_lock(&ph->sim->print_mutex);
	printf("ms: %ld id: %d has taken fork\n", get_elapsed_time(ph->sim->start_time), ph->id_philo);
	pthread_mutex_unlock(&ph->sim->print_mutex);
	pthread_mutex_lock(&ph->sim->forks[ph->right_fork]);
	pthread_mutex_lock(&ph->sim->print_mutex);
	printf("ms: %ld id: %d has taken fork\n", get_elapsed_time(ph->sim->start_time), ph->id_philo);
	pthread_mutex_unlock(&ph->sim->print_mutex);
	pthread_mutex_lock(&ph->state_mutex);
	ph->last_meal = time_in_ms();
	ph->meals_eaten++;
	pthread_mutex_unlock(&ph->state_mutex);
	pthread_mutex_lock(&ph->sim->print_mutex);
	printf("ms: %ld id: %d is EATing\n", get_elapsed_time(ph->sim->start_time), ph->id_philo);
	pthread_mutex_unlock(&ph->sim->print_mutex);
	usleep(1000 * ph->sim->time_to_eat);
	pthread_mutex_unlock(&ph->sim->forks[ph->left_fork]);
	pthread_mutex_unlock(&ph->sim->forks[ph->right_fork]);
	usleep(1000 * ph->sim->time_to_sleep);
	pthread_mutex_lock(&ph->sim->print_mutex);
	printf("ms: %ld id: %d is thinking\n", get_elapsed_time(ph->sim->start_time), ph->id_philo);
	pthread_mutex_unlock(&ph->sim->print_mutex);
}

void	odd_fork(t_philo *ph)
{
	pthread_mutex_lock(&ph->sim->forks[ph->right_fork]);
	pthread_mutex_lock(&ph->sim->print_mutex);
	printf("ms: %ld id: %d has taken fork\n", get_elapsed_time(ph->sim->start_time), ph->id_philo);
	pthread_mutex_unlock(&ph->sim->print_mutex);
	pthread_mutex_lock(&ph->sim->forks[ph->left_fork]);
	pthread_mutex_lock(&ph->sim->print_mutex);
	printf("ms: %ld id: %d has taken fork\n", get_elapsed_time(ph->sim->start_time), ph->id_philo);
	pthread_mutex_unlock(&ph->sim->print_mutex);
	pthread_mutex_lock(&ph->state_mutex);
	ph->last_meal = time_in_ms();
	ph->meals_eaten++;
	pthread_mutex_unlock(&ph->state_mutex);
	pthread_mutex_lock(&ph->sim->print_mutex);
	printf("ms: %ld id: %d is EATing\n", get_elapsed_time(ph->sim->start_time), ph->id_philo);
	pthread_mutex_unlock(&ph->sim->print_mutex);
	usleep(1000 * ph->sim->time_to_eat);
	pthread_mutex_unlock(&ph->sim->forks[ph->right_fork]);
	pthread_mutex_unlock(&ph->sim->forks[ph->left_fork]);
	usleep(1000 * ph->sim->time_to_sleep);
	pthread_mutex_lock(&ph->sim->print_mutex);
	printf("ms: %ld id: %d is thinking\n", get_elapsed_time(ph->sim->start_time), ph->id_philo);	
	pthread_mutex_unlock(&ph->sim->print_mutex);
}

void	*monitor_routine(void *philo)
{
	t_philo *ph;
	
	ph = philo;
	while (ph->is_dead != 1)
	{
		pthread_mutex_lock(&ph->state_mutex);
		if ((get_elapsed_time(ph->sim->start_time) - ph->last_meal) >= ph->sim->time_to_die)
		{
			ph->is_dead = 1;
			pthread_mutex_lock(&ph->sim->print_mutex);
			printf("ms: %ld id: %d has DIED\n", get_elapsed_time(ph->sim->start_time), ph->id_philo);
			pthread_mutex_unlock(&ph->sim->print_mutex);
			end_simulation(ph);
		}
		if (ph->meals_eaten == ph->sim->no_of_meals)
		{
			ph->enough_eaten = 1;
			pthread_mutex_lock(&ph->sim->print_mutex);
			printf("Everyone has eaten, simulation ended\n");
			end_simulation(ph);		//	TODO
			pthread_mutex_unlock(&ph->sim->print_mutex);
		}
		pthread_mutex_unlock(&ph->state_mutex);
		usleep(1000);
	}
	return (NULL);
}

void	end_simulation(t_philo *ph)
{
	pthread_mutex_destroy(&ph->sim->print_mutex);
	pthread_mutex_destroy(&ph->state_mutex);
	exit(1);
}
