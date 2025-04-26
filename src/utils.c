/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuesta- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:59:49 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/04/08 14:59:50 by mcuesta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philo.h"

int	ft_safe_atoi(char *str)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	if (!str || str[0] == '\0')
		return (-1);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-' || str[i] < '0' || str[i] > '9')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (result > 2147483647)
			return (-1);
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	return ((int)result);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	print_status(t_philo *philo, const char *status, const char *color)
{
	size_t	timestamp;

	pthread_mutex_lock(&philo->program->write_lock);
	if (!is_dead(philo->program))
	{
		timestamp = get_current_time() - philo->program->start_time;
		printf("%s[%zu] Philo %d %s%s\n", color, timestamp, philo->id, status,
			RESET);
	}
	pthread_mutex_unlock(&philo->program->write_lock);
}

void	cleanup_program(t_program *program)
{
	size_t	i;

	i = 0;
	while (i < (size_t)program->total_philos)
	{
		pthread_mutex_destroy(&program->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&program->dead_lock);
	pthread_mutex_destroy(&program->meal_lock);
	pthread_mutex_destroy(&program->write_lock);
	pthread_mutex_destroy(&program->monitor_lock);
	free(program->forks);
	free(program->philos);
	free(program->state);
	free(program->threads);
}
