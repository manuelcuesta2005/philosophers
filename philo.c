/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuesta- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:01:39 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/04/08 15:01:41 by mcuesta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	main(int argc, char **argv)
{
	t_program	program;
	pthread_t	*threads;
	int			i;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: ./philo number_of_philos time_to_die time_to_eat time_to_sleep [number_of_times_each_philo_must_eat]\n");
		return (1);
	}
	init_program(argv, &program);
	threads = malloc(sizeof(pthread_t) * program.total_philos);
	if (!threads)
	{
		printf("Error allocating thread array.\n");
		return (1);
	}

	i = 0;
	while (i < program.total_philos)
	{
		if (pthread_create(&threads[i], NULL, routine_philo,
				(void *)&program.philos[i]) != 0)
		{
			printf("Error creating thread for philosopher %d\n", i);
			return (1);
		}
		i++;
	}

	i = 0;
	while (i < program.total_philos)
	{
		if (pthread_join(threads[i], NULL) != 0)
		{
			printf("Error joining thread for philosopher %d\n", i);
			return (1);
		}
		i++;
	}

	// Limpieza final
	i = 0;
	while (i < program.total_philos)
	{
		pthread_mutex_destroy(program.philos[i].left_fork);
		pthread_mutex_destroy(program.philos[i].rigth_fork);
		i++;
	}
	free(threads);
	destroy_program(&program);
	return (0);
}
