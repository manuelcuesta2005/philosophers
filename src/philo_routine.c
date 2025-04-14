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
	pthread_mutex_lock(&philo->program->monitor_lock);
	print_status(philo, "is eating", GREEN);
	philo->last_eaten_time = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->program->monitor_lock);
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

	philo = (t_philo *)arg;
	while (!is_dead(philo->program))
	{
		print_status(philo, "is thinking", BLUE);
		ft_usleep(philo->time_sleep);

		take_forks(philo->id, philo->program);
		eat_philo(philo);
		
		put_forks(philo->id, philo->program);
		print_status(philo, "is sleeping", YELLOW);
		ft_usleep(philo->time_sleep);
	}
	return (NULL);
}
