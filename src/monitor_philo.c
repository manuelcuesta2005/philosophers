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
    program->state[i - 1] = HUNGRY;
    test(i, program);
    pthread_mutex_unlock(&program->monitor_lock);
    while (1)
    {
        pthread_mutex_lock(&program->monitor_lock);
        if (program->state[i - 1] == EATING)
        {
            pthread_mutex_unlock(&program->monitor_lock);
            break;
        }
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
    if (program->state[i - 1] == EATING)
    {
        program->state[i - 1] = THINKING;
        pthread_mutex_unlock(program->philos[i - 1].left_fork);
        pthread_mutex_unlock(program->philos[i - 1].rigth_fork);
    }
    test(left, program);
    test(right, program);
    pthread_mutex_unlock(&program->monitor_lock);
}

void	test(int i, t_program *program)
{
	int	left;
	int right;
    t_philo *philo;

	left = (i + program->total_philos - 1) % program->total_philos;
	right = (i + 1) % program->total_philos;
    philo = &program->philos[i];
	if(program->state[i - 1] == HUNGRY && 
        program->state[left] != EATING && 
        program->state[right] != EATING)
	{
        program->state[i - 1] = EATING;
        pthread_mutex_lock(philo->left_fork);
        print_status(philo, "has taken the left fork", MAGENTA);
        pthread_mutex_lock(philo->rigth_fork);
        print_status(philo, "has taken the right fork", MAGENTA);

        pthread_mutex_lock(&program->monitor_lock);
        philo->last_eaten_time = get_current_time();
        philo->meals_eaten++;
        pthread_mutex_unlock(&program->monitor_lock);
        print_status(philo, "is eating", GREEN);
	}
}

void    *monitor(void *arg)
{
    t_program *program;
    int i;

    program = (t_program *)arg;
    i = 0;
    while(!is_dead(program))
    {
        i = 0;
        while(i < program->total_philos)
        {
            pthread_mutex_lock(&program->monitor_lock);
            if ((int)(get_current_time() - program->philos[i].last_eaten_time) > program->philos[i].time_die)
            {
                print_status(&program->philos[i], "died", RED);
                pthread_mutex_lock(&program->dead_lock);
                program->dead = 1;
                pthread_mutex_unlock(&program->dead_lock);
                return(NULL);
            }
            pthread_mutex_unlock(&program->monitor_lock);
            i++;
        }
        ft_usleep(1000);
    }
    return (NULL);
}
