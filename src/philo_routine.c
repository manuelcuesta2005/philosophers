/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuesta- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:54:58 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/04/09 15:54:59 by mcuesta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philo.h"

void	eat_philo(t_philo *philo)
{
	ft_usleep(philo->time_eat);
}

int	is_dead(t_program *program)
{
	int	dead;

	pthread_mutex_lock(&program->dead_lock);
	dead = program->dead;
	pthread_mutex_unlock(&program->dead_lock);
	return (dead);
}

void	*routine_philo(void *arg)
{
	t_philo	*philo;
	int	index;

	philo = (t_philo *)arg;
	index = philo->id - 1;
	if (philo->id % 2 == 0)
		ft_usleep(200);
	while (!is_dead(philo->program))
	{
		print_status(philo, "is thinking", BLUE);
		take_forks(index, philo->program);
		if (is_dead(philo->program))
			break ;
		eat_philo(philo);
		print_status(philo, "is sleeping", YELLOW);
		ft_usleep(philo->time_sleep);
		put_forks(index, philo->program);
	}
	return (NULL);
}
