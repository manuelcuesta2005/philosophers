/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuesta- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:33:30 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/04/08 14:33:31 by mcuesta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philo.h"

void	init_philo(char **argv, pthread_mutex_t *forks, t_program *program)
{
	int		i;
	int		total_philos;
	t_philo	*philos;

	i = 0;
	total_philos = program->total_philos;
	philos = malloc(sizeof(t_philo) * total_philos);
	if (!philos)
		return ;
	while (i < total_philos)
	{
		philos[i].id = i + 1;
		philos[i].time_die = ft_atoi(argv[2]);
		philos[i].time_eat = ft_atoi(argv[3]);
		philos[i].time_sleep = ft_atoi(argv[4]);
		philos[i].meals_eaten = 0;
		philos[i].left_fork = &forks[i];
		philos[i].rigth_fork = &forks[(i + 1) % total_philos];
		philos[i].program = program;
		philos[i].last_eaten_time = philos->program->start_time;
		i++;
	}
	program->philos = philos;
}

void	init_forks(int total_philos, t_program *program)
{
	int				i;
	pthread_mutex_t	*forks;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * total_philos);
	if (!forks)
		return ;
	while (i < total_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	program->total_forks = forks;
}

void	init_program(char **argv, t_program *program)
{
	int		i;

	i = 0;
	program->total_philos = ft_atoi(argv[1]);
	program->dead = 0;
	program->state = malloc(sizeof(int) * program->total_philos);
	if (!program->state)
		return ;
	while(i < program->total_philos)
	{
		program->state[i] = THINKING;
		i++;
	}
	program->start_time = get_current_time();
	init_forks(program->total_philos, program);
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->monitor_lock, NULL);
	init_philo(argv, program->total_forks, program);
}

void	destroy_program(t_program *program)
{
	int	i;
	
	i = 0;
	if (program->philos)
		free(program->philos);
	if (program->state)
		free(program->state);
	if (program->total_forks)
	{
		i = 0;
		while (i < program->total_philos)
		{
			pthread_mutex_destroy(&program->total_forks[i]);
			i++;
		}
		free(program->total_forks);
	}
	pthread_mutex_destroy(&program->dead_lock);
	pthread_mutex_destroy(&program->meal_lock);
	pthread_mutex_destroy(&program->write_lock);
	pthread_mutex_destroy(&program->monitor_lock);
}
