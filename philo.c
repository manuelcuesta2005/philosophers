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

int	launch_threads(t_program *program)
{
	size_t	i;

	i = 0;
	program->threads = malloc(sizeof(pthread_t) * program->total_philos);
	if (!program->threads)
		return (0);
	while (i < (size_t)program->total_philos)
	{
		if (pthread_create(&program->threads[i], NULL, routine_philo,
				(void *)&program->philos[i]) != 0)
		{
			printf("Error creating thread %zu\n", i);
			return (0);
		}
		i++;
	}
	return (1);
}

int	wait_threads(t_program *program)
{
	size_t	i;

	i = 0;
	while (i < (size_t)program->total_philos)
	{
		if (pthread_join(program->threads[i], NULL) != 0)
		{
			printf("Error joining thread %zu\n", i);
			return (0);
		}
		i++;
	}
	return (1);
}

int	launch_monitor(pthread_t *monitor_thread, t_program *program)
{
	if (pthread_create(monitor_thread, NULL, monitor, (void *)program) != 0)
	{
		printf("Error creating monitor thread\n");
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_program	program;
	pthread_t	monitor_thread;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: ./philo number_of_philos time_to_die time_to_eat time_to_sleep [number_of_times_each_philo_must_eat]\n");
		return (1);
	}
	if (!parse_arguments(argv))
		return (1);
	init_program(argv, &program);
	if (!launch_threads(&program))
		return (1);
	if (!launch_monitor(&monitor_thread, &program))
		return (1);
	if (!wait_threads(&program))
		return (1);
	pthread_join(monitor_thread, NULL);
	cleanup_program(&program);
	return (0);
}
