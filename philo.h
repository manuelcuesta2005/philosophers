/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuesta- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:34:04 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/04/08 14:34:06 by mcuesta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

// DIE COLOR
# define RED "\033[0;31m"
// EAT COLOR
# define GREEN "\033[0;32m"
// SLEEP COLOR
# define YELLOW "\033[0;33m"
// THINK COLOR
# define BLUE "\033[0;34m"
// FORK COLOR
# define MAGENTA "\033[0;35m"
// RESET COLOR
# define RESET "\033[0m"

# define THINKING 0
# define HUNGRY 1
# define EATING 2

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	size_t				time_die;
	size_t				time_eat;
	size_t				time_sleep;
	size_t				meals_eaten;
	size_t				last_eaten_time;
	pthread_mutex_t		*rigth_fork;
	pthread_mutex_t		*left_fork;
	struct s_program	*program;
}						t_philo;

typedef struct s_program
{
	int					total_philos;
	int					*state;
	size_t				dead;
	size_t				start_time;
	size_t				meals_required;
	size_t				philosophers_done;
	pthread_t			*threads;
	pthread_mutex_t		*forks;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		write_lock;
	pthread_mutex_t		monitor_lock;
	t_philo				*philos;
}						t_program;
//  parse
int						ft_safe_atoi(char *str);
int						valid_numbers(char *argv);
int						valid_arguments(int argc, char **argv);
int						parse_arguments(char **argv);
//  start program
void					init_philo(char **argv, pthread_mutex_t *forks,
							t_program *program);
void					init_forks(int total_philos, t_program *program);
void					init_program(char **argv, t_program *program);
void					destroy_program(t_program *program);
//	Routine philo
void					*routine_philo(void *arg);
void					eat_philo(t_philo *philo);
int						is_dead(t_program *program);
// Monitor philo
void					take_forks(size_t i, t_program *program);
void					put_forks(size_t i, t_program *program);
void					test(size_t i, t_program *program);
void					*monitor(void *arg);
// utils
int						ft_usleep(size_t milliseconds);
size_t					get_current_time(void);
void					print_status(t_philo *philo, const char *status,
							const char *color);
void					cleanup_program(t_program *program);
#endif