/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwrzosek <kwrzosek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:44:03 by kwrzosek          #+#    #+#             */
/*   Updated: 2025/09/25 22:20:55 by kwrzosek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

/*		STRUCTS		*/

typedef struct s_philo	t_philo;

typedef struct s_sim_params
{
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					no_of_meals;

	long				start_time;
	int					no_of_philo;
	pthread_t			*threads;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		stop_mutex;
	int					stop;
	pthread_t			monitor;
	t_philo				*philos;
}						t_sim_params;

struct					s_philo
{
	int					id_philo;
	int					left_fork;
	int					right_fork;
	long				last_meal;
	int					meals_eaten;
	int					enough_eaten;
	int					is_dead;
	pthread_mutex_t		state_mutex;
	t_sim_params		*sim;
};

/*		FUNCTIONS	*/

/*	main.c	*/
int						main(int argc, char **argv);

/*	routine.c	*/
void					*routine(void *arg);
int						even_fork(t_philo *ph);
int						odd_fork(t_philo *ph);
void					*monitor_routine(void *arg);
void					end_simulation(t_sim_params *sim);

/*	fork_utils.c	*/
int						handle_forks(t_philo *ph, int first, int second);
int						check_death(t_sim_params *sim, t_philo *ph);
int						check_full(t_sim_params *sim);

/*	utils.c	*/
int						validate_args(int argc, char **argv);
long					get_elapsed_time(long start_time);
long					time_in_ms(void);

/*	routine_utils.c	*/
int						print_msg(t_philo *ph, char *msg);
void					ft_sleep(long ms);
int						should_continue(t_philo *ph);
int						update_state(t_philo *ph);
int						finish_cycle(t_philo *ph);

/*	init.c	*/
int						init_sim(t_sim_params *sim, int argc, char **argv);
int						init_philos(t_sim_params *sim);
int						init_forks(t_sim_params *sim);
int						create_threads(t_sim_params *sim);
int						join_threads(t_sim_params *sim);

#endif
