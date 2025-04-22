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

int	ft_atoi(char *nbr)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	while (nbr[i] == ' ' || (nbr[i] >= 9 && nbr[i] <= 13))
	{
		i++;
	}
	if (nbr[i] == '+' || nbr[i] == '-')
	{
		if (nbr[i] == '-')
		{
			sign = -sign;
		}
		i++;
	}
	while (nbr[i] >= '0' && nbr[i] <= '9')
	{
		result = result * 10 + (nbr[i] - '0');
		i++;
	}
	return (result * sign);
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
		printf("%s[%zu] Philo %d %s%s\n", color, timestamp, philo->id, status, RESET);
	}
	pthread_mutex_unlock(&philo->program->write_lock);
}