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

void	block_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->program->write_lock);
	printf(MAGENTA "Philo %d has taken the left fork\n" RESET, philo->id);
	pthread_mutex_unlock(&philo->program->write_lock);
	pthread_mutex_lock(philo->rigth_fork);
	pthread_mutex_lock(&philo->program->write_lock);
	printf(MAGENTA "Philo %d has taken the right fork\n" RESET, philo->id);
	pthread_mutex_unlock(&philo->program->write_lock);
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->rigth_fork);
}

void	eat_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->meal_lock);
	printf(GREEN "Philo %d is eating\n" RESET, philo->id);
	philo->last_eaten_time = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->program->meal_lock);
	ft_usleep(philo->time_eat);
	unlock_forks(philo);
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
		pthread_mutex_lock(&philo->program->write_lock);
		printf(BLUE "Philo %d is thinking\n" RESET, philo->id);
		pthread_mutex_unlock(&philo->program->write_lock);
		usleep(100);
		block_forks(philo);
		eat_philo(philo);
		pthread_mutex_lock(&philo->program->write_lock);
		printf(YELLOW "Philo %d is sleeping\n" RESET, philo->id);
		pthread_mutex_unlock(&philo->program->write_lock);
		ft_usleep(philo->time_sleep);
	}
	return (NULL);
}
