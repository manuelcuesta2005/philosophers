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

void    take_forks(int i, t_program *program)
{
    pthread_mutex_lock(&program->monitor_lock);
    program->state[i] = HUNGRY;
    test(i, program);
    pthread_mutex_unlock(&program->monitor_lock);
    while (program->state[i] != EATING)
    {
        pthread_mutex_lock(&program->monitor_lock);
        test(i, program);
        pthread_mutex_unlock(&program->monitor_lock);
        ft_usleep(100);
    }
}

void    put_forks(int i, t_program *program)
{
	int	left;
	int right;

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

void	test(int i, t_program *program)
{
	int	left;
	int right;
	t_philo	*philo;

	philo = &program->philos[i];
	left = (i + program->total_philos - 1) % program->total_philos;
	right = (i + 1) % program->total_philos;
	if(program->state[i] == HUNGRY && 
        program->state[left] != EATING && 
        program->state[right] != EATING)
	{
		program->state[i] = EATING;
        pthread_mutex_lock(philo->left_fork);
        print_status(philo, "has taken the left fork", MAGENTA);
		pthread_mutex_lock(philo->rigth_fork);
        print_status(philo, "has taken the right fork", MAGENTA);
        printf("Philo %d sees: left (%d) = %d, right (%d) = %d\n",
        i, left, program->state[left],
        right, program->state[right]);

	}
}
