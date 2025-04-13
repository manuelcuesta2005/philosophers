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
	pthread_mutex_lock(&philo->program->meal_lock);
	printf(GREEN "Philo %d is eating\n" RESET, philo->id);
	philo->last_eaten_time = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->program->meal_lock);
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
		printf(BLUE "Philo %d is thinking\n" RESET, philo->id);
		usleep(100);

		take_forks(philo->id, philo->program);
		eat_philo(philo);
		
		printf(YELLOW "Philo %d is sleeping\n" RESET, philo->id);
		ft_usleep(philo->time_sleep);

		put_forks(philo->id, philo->program);
	}
	return (NULL);
}
