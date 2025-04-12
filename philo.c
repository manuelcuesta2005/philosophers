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
	t_philo		*philo;
	int			i;
	pthread_t	*threads;

	if (argc < 5)
	{
		printf("Usage: ./philo number_of_philos time_to_die time_to_eat time_to_sleep\n");
		return (1);
	}
	init_program(argv, &program);
	threads = malloc(sizeof(pthread_t) * program.total_philos);
	if (!threads)
		return (1);
	// Crear los hilos para cada filósofo
	i = 0;
	while (i < program.total_philos)
	{
		philo = &program.philos[i];
		pthread_create(&threads[i], NULL, routine_philo,
			(void *)&program.philos[i]);
		i++;
	}
	// Esperar a que todos los hilos terminen
	i = 0;
	while (i < program.total_philos)
	{
		if (pthread_join(threads[i], NULL) != 0)
		{
			printf("Error joining thread for philosopher %d\n",
				program.philos[i].id);
			return (1);
		}
		i++;
	}
	// Liberar recursos
	free(threads);
	free(program.philos);
	free(program.total_forks);
	return (0);
}
