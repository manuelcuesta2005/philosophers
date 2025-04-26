/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuesta- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:19:14 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/04/12 14:19:16 by mcuesta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philo.h"

void	take_forks(size_t i, t_program *program)
{
	pthread_mutex_lock(&program->monitor_lock);
	program->state[i] = HUNGRY;
	test(i, program);
	pthread_mutex_unlock(&program->monitor_lock);
	while (1)
	{
		pthread_mutex_lock(&program->monitor_lock);
		if (program->state[i] == EATING)
		{
			pthread_mutex_unlock(&program->monitor_lock);
			break ;
		}
		pthread_mutex_unlock(&program->monitor_lock);
		ft_usleep(100);
	}
}

void	put_forks(size_t i, t_program *program)
{
	size_t	left;
	size_t	right;

	left = (i + program->total_philos - 1) % program->total_philos;
	right = (i + 1) % program->total_philos;
	pthread_mutex_lock(&program->monitor_lock);
	if (program->state[i] == EATING)
	{
		program->state[i] = THINKING;
		pthread_mutex_unlock(program->philos[i].left_fork);
		pthread_mutex_unlock(program->philos[i].rigth_fork);
	}
	test(left, program);
	test(right, program);
	pthread_mutex_unlock(&program->monitor_lock);
}

void	test(size_t i, t_program *program)
{
	size_t		left;
	size_t		right;
	t_philo		*philo;

	left = (i + program->total_philos - 1) % program->total_philos;
	right = (i + 1) % program->total_philos;
	philo = &program->philos[i];
	if (program->state[i] == HUNGRY && program->state[left] != EATING
		&& program->state[right] != EATING)
	{
		program->state[i] = EATING;
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken the left fork", MAGENTA);
		pthread_mutex_lock(philo->rigth_fork);
		print_status(philo, "has taken the right fork", MAGENTA);
	}
}

void    test_meals(t_program *program)
{
    size_t i;

    if (program->meals_required > 0)
    {
        pthread_mutex_lock(&program->meal_lock);
        i = 0;
        while (i < (size_t)program->total_philos)
        {
            if (program->philos[i].meals_eaten < program->meals_required)
                break;
            i++;
        }
        if (i == (size_t)program->total_philos ||
            program->philosophers_done == (size_t)program->total_philos)
        {
            pthread_mutex_unlock(&program->meal_lock);
		    pthread_mutex_lock(&program->dead_lock);
		    program->dead = 1;
		    pthread_mutex_unlock(&program->dead_lock);
		    return ;
        }
        pthread_mutex_unlock(&program->meal_lock);
    }
}

void	*monitor(void *arg)
{
	size_t		i;
	t_program	*program;

	program = (t_program *)arg;
	while (!is_dead(program))
	{
		i = 0;
		while (i < (size_t)program->total_philos)
		{
            pthread_mutex_lock(&program->monitor_lock);
            test_meals(program);
			if ((get_current_time() - program->philos[i].last_eaten_time)
				>= program->philos[i].time_die)
			{
				print_status(&program->philos[i], "died", RED);
				pthread_mutex_lock(&program->dead_lock);
				program->dead = 1;
				pthread_mutex_unlock(&program->dead_lock);
                pthread_mutex_unlock(&program->monitor_lock);
				return (NULL);
			}
			pthread_mutex_unlock(&program->monitor_lock);
			i++;
		}
		ft_usleep(500);
	}
	return (NULL);
}
