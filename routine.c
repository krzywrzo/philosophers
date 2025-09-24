/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwrzosek <kwrzosek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:01:05 by kwrzosek          #+#    #+#             */
/*   Updated: 2025/09/24 16:06:17 by kwrzosek         ###   ########.fr       */
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
	while (!ph->sim->stop && (ph->sim->no_of_meals < 0
			|| ph->meals_eaten < ph->sim->no_of_meals))
	{
		if (ph->id_philo % 2 == 0)
			even_fork(ph);
		else
			odd_fork(ph);
	}
	// end_simulation();	TODO
	return (NULL);
}

// void	*routine(void *philo)
// {
// 	t_philo	*ph;

// 	ph = (t_philo *)philo;
// 	if (ph->sim->no_of_philo == 1)
// 	{
// 		pthread_mutex_lock(&ph->sim->print_mutex);
// 		printf("%ld %d has taken a fork\n",
// 			get_elapsed_time(ph->sim->start_time), ph->id_philo + 1);
// 		pthread_mutex_unlock(&ph->sim->print_mutex);
// 		usleep(ph->sim->time_to_die * 1000);
// 		pthread_mutex_lock(&ph->sim->print_mutex);
// 		printf("%ld %d died\n",
// 			get_elapsed_time(ph->sim->start_time), ph->id_philo + 1);
// 		pthread_mutex_unlock(&ph->sim->print_mutex);
// 		ph->is_dead = 1;
// 		ph->sim->stop = 1;
// 		return (NULL);
// 	}
// 	while ((ph->sim->stop == 0 && ph->is_dead == 0) && (ph->sim->no_of_meals == -1
// 			|| ph->meals_eaten < ph->sim->no_of_meals))
// 	{
// 		if (ph->id_philo % 2 == 0)
// 		{
// 			if (even_fork(ph) != 0)
// 					end_simulation(ph);
// 		}
// 		else
// 		{
// 			if (odd_fork(ph) != 0)
// 				end_simulation(ph);
// 		}
// 	}
// 	return (NULL);
// }

int	even_fork(t_philo *ph)
{
	if (pthread_mutex_lock(&ph->sim->forks[ph->left_fork]) != 0)
		return (1);
	if (print_msg(ph, "has taken a fork"))
		return (pthread_mutex_unlock(&ph->sim->forks[ph->left_fork]), 1);

	if (pthread_mutex_lock(&ph->sim->forks[ph->right_fork]) != 0)
		return (1);
	if (print_msg(ph, "has taken a fork"))
	{
		pthread_mutex_unlock(&ph->sim->forks[ph->right_fork]);
		pthread_mutex_unlock(&ph->sim->forks[ph->left_fork]);
		return (1);
	}

	pthread_mutex_lock(&ph->state_mutex);
	ph->last_meal = time_in_ms();
	ph->meals_eaten++;
	pthread_mutex_unlock(&ph->state_mutex);

	if (print_msg(ph, "is eating"))
	{
		pthread_mutex_unlock(&ph->sim->forks[ph->left_fork]);
		pthread_mutex_unlock(&ph->sim->forks[ph->right_fork]);
		return (1);
	}

	ft_sleep(ph->sim->time_to_eat);

	pthread_mutex_unlock(&ph->sim->forks[ph->left_fork]);
	pthread_mutex_unlock(&ph->sim->forks[ph->right_fork]);

	if (print_msg(ph, "is sleeping"))
		return (1);
	ft_sleep(ph->sim->time_to_sleep);

	if (print_msg(ph, "is thinking"))
		return (1);
	return (0);
}

int	odd_fork(t_philo *ph)
{
	if (pthread_mutex_lock(&ph->sim->forks[ph->right_fork]) != 0)
		return (1);
	if (print_msg(ph, "has taken a fork"))
		return (pthread_mutex_unlock(&ph->sim->forks[ph->right_fork]), 1);

	if (pthread_mutex_lock(&ph->sim->forks[ph->left_fork]) != 0)
		return (1);
	if (print_msg(ph, "has taken a fork"))
	{
		pthread_mutex_unlock(&ph->sim->forks[ph->left_fork]);
		pthread_mutex_unlock(&ph->sim->forks[ph->right_fork]);
		return (1);
	}

	pthread_mutex_lock(&ph->state_mutex);
	ph->last_meal = time_in_ms();
	ph->meals_eaten++;
	pthread_mutex_unlock(&ph->state_mutex);

	if (print_msg(ph, "is eating"))
	{
		pthread_mutex_unlock(&ph->sim->forks[ph->right_fork]);
		pthread_mutex_unlock(&ph->sim->forks[ph->left_fork]);
		return (1);
	}

	ft_sleep(ph->sim->time_to_eat);

	pthread_mutex_unlock(&ph->sim->forks[ph->right_fork]);
	pthread_mutex_unlock(&ph->sim->forks[ph->left_fork]);

	if (print_msg(ph, "is sleeping"))
		return (1);
	ft_sleep(ph->sim->time_to_sleep);

	if (print_msg(ph, "is thinking"))
		return (1);
	return (0);
}

// void    *monitor_routine(void *arg)
// {
//     t_sim_params *sim;
//     t_philo      *ph;
//     int           i;
//     int           full_count;

//     sim = (t_sim_params *)arg;
//     while (!sim->stop)
//     {
//         full_count = 0;
//         i = 0;
//         while (i < sim->no_of_philo)
//         {
//             ph = &sim->philos[i];
//             pthread_mutex_lock(&ph->state_mutex);
//             if (time_in_ms() - ph->last_meal >= sim->time_to_die)
//             {
//                 pthread_mutex_lock(&sim->print_mutex);
//                 if (!sim->stop)
//                     printf("%ld %d died\n",
//                         get_elapsed_time(sim->start_time), ph->id_philo + 1);
//                 sim->stop = 1;
//                 pthread_mutex_unlock(&sim->print_mutex);
//                 pthread_mutex_unlock(&ph->state_mutex);
//                 return (NULL);
//             }
//             if (sim->no_of_meals > 0
//                 && ph->meals_eaten >= sim->no_of_meals)
//                 full_count++;
//             pthread_mutex_unlock(&ph->state_mutex);
//             i++;
//         }
//         if (sim->no_of_meals > 0 && full_count == sim->no_of_philo)
//         {
//             pthread_mutex_lock(&sim->print_mutex);
//             sim->stop = 1;
//             pthread_mutex_unlock(&sim->print_mutex);
//             return (NULL);
//         }
//         usleep(1000); // finer granularity
//     }
//     return (NULL);
// }


void    *monitor_routine(void *arg)
{
    t_sim_params *sim;
    t_philo      *ph;
    int           i;
    int           full_count;

    sim = (t_sim_params *)arg;
    while (!sim->stop)
    {
        full_count = 0;
        i = 0;
        while (i < sim->no_of_philo)
        {
            ph = &sim->philos[i];
            pthread_mutex_lock(&ph->state_mutex);
            if (time_in_ms() - ph->last_meal > sim->time_to_die)
            {
                pthread_mutex_lock(&sim->print_mutex);
                if (!sim->stop)
				{

					// printf("	SIM->STOP=%d\n", sim->stop);
					// printf("	ID: %d SINCE EATING: %ld\n",ph->id_philo, time_in_ms() - ph->last_meal);
                    printf("%ld %d died\n",
                        get_elapsed_time(sim->start_time), ph->id_philo + 1);}
                pthread_mutex_unlock(&sim->print_mutex);
                sim->stop = 1;
                pthread_mutex_unlock(&ph->state_mutex);
                return (NULL);
            }
            if (sim->no_of_meals > 0
                && ph->meals_eaten >= sim->no_of_meals)
                full_count++;
            pthread_mutex_unlock(&ph->state_mutex);
            i++;
        }
        if (sim->no_of_meals > 0 && full_count == sim->no_of_philo)
            sim->stop = 1;
        ft_sleep(1);
    }
    return (NULL);
}

void	end_simulation(t_sim_params *sim)
{
	int	i;

	i = 0;
	pthread_join(sim->monitor, NULL);
	while(i < sim->no_of_philo)
	{
		pthread_join(sim->threads[i], NULL);
		pthread_mutex_destroy(&sim->forks[i]);
		pthread_mutex_destroy(&sim->philos[i].state_mutex);
		i++;
	}
	pthread_mutex_destroy(&sim->print_mutex);
	free(sim->philos);
	free(sim->forks);
	free(sim->threads);
	free(sim);
}
