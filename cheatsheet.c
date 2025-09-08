/*
		// 	CREATING MULTIPLE THREADS IN LOOP, WITH PASSING ARG TO ROUTINE
		int i = 0;
		int	*a;
		pthread_t	philos[number_of_philo];

		while (i <= number_of_philo)
		{
			a = malloc(sizeof(int*));
			*a = i;
			pthread_create(philos + i, NULL, &routine, a);
			i++;
		}
		i = 0;
		while (i <= number_of_philo)
		{
			pthread_join(philos[i], NULL);
			i++;
		}
*/
		
		// Routine func: (order depends on id_philo (odd or even))
		// ft_eat();			
		// ft_sleep();			
		// ft_think();			

// FORKS 
	// id_philo % 2 == 0 fork: N + 1
	// id_philo % 2 != 0 fork: N - 1


int create_threads(sim_params *sim)
{
    int i;

    i = 0;
    while (i < sim->no_of_philo)
    {
        if (pthread_create(&sim->threads[i], NULL,
                routine, &sim->philos[i]) != 0)
            return (print_error(2));
        i++;
    }
    i = 0;
    while (i < sim->no_of_philo)
    {
        if (pthread_join(sim->threads[i], NULL) != 0)
            return (print_error(3));
        i++;
    }
    return (0);
}


/* 
	argv (in ms): 
	-> 1 - number_of_philo 
	-> 2 - time_to_die (since last meal)
	-> 3 - time_to_eat (time they need to eat, they need 2 forks for this)
	-> 4 - time_to_sleep (time for sleeping)
	-> 5 - numbers_of_time_each_philo_must_eat (optional)

*/