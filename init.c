/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwrzosek <kwrzosek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:53:35 by kwrzosek          #+#    #+#             */
/*   Updated: 2025/09/07 19:37:04 by kwrzosek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_sim(t_sim_params *sim, int argc, char **argv)	// FIXME: error returns 
{
	if (argc < 5 || argc > 6)
		return (1);
	sim->no_of_philo = atoi(argv[1]);
	sim->time_to_die = atoi(argv[2]);
	sim->time_to_eat = atoi(argv[3]);
	sim->time_to_sleep = atoi(argv[4]);
	sim->no_of_meals = (argc == 6) ? atoi(argv[5]) : -1;
	if (sim->no_of_philo <= 0 || sim->time_to_die <= 0
		|| sim->time_to_eat <= 0 || sim->time_to_sleep <= 0)
		return (1);
	sim->threads = malloc(sizeof(pthread_t) * sim->no_of_philo);
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->no_of_philo);
	sim->philos = malloc(sizeof(t_philo) * sim->no_of_philo);
	if (!sim->threads || !sim->forks || !sim->philos)
		return (1);
	if (pthread_mutex_init(&sim->print_mutex, NULL) != 0)
		return (1);
	sim->stop = 0;
	sim->start_time = time_in_ms();
	return (0);
}

int	init_philos(t_sim_params *sim)
{
	int		i;
	t_philo	*p;

	i = 0;
	while (i < sim->no_of_philo)
	{
		p = &sim->philos[i];
		p->id_philo = i;
		p->left_fork = i;
		p->right_fork = (i + 1) % sim->no_of_philo;
		p->meals_eaten = 0;
		p->last_meal = sim->start_time;
		p->sim = sim;
		if (pthread_mutex_init(&p->state_mutex, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	init_forks(t_sim_params *sim)	// FIXME: error returns 
{
	int	i;

	i = 0;
	while (i < sim->no_of_philo)
	{
		if (pthread_mutex_init(&sim->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int create_threads(t_sim_params *sim)	// FIXME: norminette
{
    int i;

    i = 0;
	pthread_t monitor;

	
	
	while (i < sim->no_of_philo)
	{
		pthread_mutex_init(&sim->forks[i], NULL);
		i++;
	}
	i = 0;
    while (i < sim->no_of_philo)
    {
		pthread_create(&sim->threads[i], NULL, routine, &sim->philos[i]);
		pthread_create(&monitor, NULL, monitor_routine, &sim->philos[i]);
		i++;
    }
    i = 0;
    while (i < sim->no_of_philo)
    {
		pthread_join(sim->threads[i], NULL);
		pthread_join(monitor, NULL);
        i++;
    }
	i = 0;
	while (i < sim->no_of_philo)
	{
		pthread_mutex_destroy(&sim->forks[i]);
		i++;
	}
	
    return (0);
}
