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
	philo->meals_eaten++;
	philo->last_eaten_time = get_current_time();
	print_status(philo, "is eating", GREEN);
	ft_usleep(philo->time_eat);
	if (philo->program->meals_required > 0 && philo->meals_eaten == philo->program->meals_required)
	{
		pthread_mutex_lock(&philo->program->meal_lock);
		philo->program->philosophers_done++;
		pthread_mutex_unlock(&philo->program->meal_lock);
	}
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
	if (philo->id % 2 == 0)
		ft_usleep(200);
	while (!is_dead(philo->program))
	{
		take_forks(philo->id - 1, philo->program);
		if (is_dead(philo->program))
		{
			put_forks(philo->id - 1, philo->program);
			break ;
		}
		eat_philo(philo);
		put_forks(philo->id - 1, philo->program);
		if (is_dead(philo->program))
			break ;
		print_status(philo, "is sleeping", YELLOW);
		ft_usleep(philo->time_sleep);
		if (is_dead(philo->program))
			break ;
		print_status(philo, "is thinking", BLUE);
		ft_usleep(philo->time_sleep);
	}
	return (NULL);
}
