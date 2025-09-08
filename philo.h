# ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

/*		STRUCTS		*/

typedef struct s_philo t_philo;

typedef struct s_sim_params
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				no_of_meals;
	
	long			start_time;
	int				no_of_philo;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	int				stop;
	t_philo			*philos;
}	t_sim_params;

struct s_philo
{
	int				id_philo;
	int				left_fork;
	int				right_fork;
	long			last_meal;
	int				meals_eaten;
	int				enough_eaten;
	int				is_dead;
	pthread_mutex_t	state_mutex;
	t_sim_params	*sim;
};

/*		FUNCTIONS	*/

//	routine.c
void	*routine(void *ph);
void	*monitor_routine(void *philo);
void	even_fork(t_philo *ph);
void	odd_fork(t_philo *ph);
void	end_simulation(t_philo *ph);

//	init.c
int		init_sim(t_sim_params *sim, int argc, char **argv);
int		init_philos(t_sim_params *sim);
int		init_forks(t_sim_params *sim);
int 	create_threads(t_sim_params *sim);

//	utils.c
int		print_error(int flag);
int		validate_args(int argc, char **argv);
long	get_elapsed_time(long start_time);
long	time_in_ms();
int		is_dead (t_philo *ph);

# endif