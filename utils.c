/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwrzosek <kwrzosek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 15:11:43 by kwrzosek          #+#    #+#             */
/*   Updated: 2025/09/25 22:22:08 by kwrzosek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	validate_args(int argc, char **argv)
{
	int	i;

	i = 2;
	if (atoi(argv[1]) < 1)
		return (1);
	while (i < argc)
	{
		if (atoi(argv[i]) <= 0)
			return (1);
		i++;
	}
	return (0);
}

long	get_elapsed_time(long start_time)
{
	struct timeval	tv;
	long			ms;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (ms - start_time);
}

long	time_in_ms(void)
{
	long			ms;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (ms);
}
