/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuesta- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:33:42 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/04/08 14:33:43 by mcuesta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../philo.h"

int	valid_numbers(char *argv)
{
	int	i;

	if (!argv || argv[0] == '\0')
		return (0);
	i = 0;
	while (argv[i])
	{
		if (argv[i] < '0' || argv[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	valid_arguments(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!valid_numbers(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

// int	parse_arguments(int argc, char **argv)
// {
// 	int philos;
// 	int die;
// 	int eat;
// 	int sleep;

// 	if (argc != 5 && argc != 6)
// 	{
// 		printf("Usage: ./philo number_of_philos time_to_die time_to_eat time_to_sleep [number_of_times_each_philo_must_eat]\n");
// 		return (0);
// 	}

// 	if (ft_safe_atoi(argv[1]) <= 0 || ft_safe_atoi(argv[1]) >= 200)
// 	{
// 		printf("Error, the program only allows less than 200 philosophers \n");
// 		return (0);
// 	}
// 	if (ft_safe_atoi(argv[2]) <= 60 || ft_safe_atoi(argv[3]) <= 60
//		|| ft_safe_atoi(argv[4]) <= 60)
// 	{
// 		printf("Error, the time for action is very short for philosophers \n");
// 		return (0);
// 	}
// 	return (1);
// }

int	parse_arguments(int argc, char **argv)
{
	int	philos;
	int	die;
	int	eat;
	int	sleep;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: ./philo number_of_philos time_to_die time_to_eat time_to_sleep [number_of_times_each_philo_must_eat]\n");
		return (0);
	}
	philos = ft_safe_atoi(argv[1]);
	die = ft_safe_atoi(argv[2]);
	eat = ft_safe_atoi(argv[3]);
	sleep = ft_safe_atoi(argv[4]);
	if (philos == -1 || die == -1 || eat == -1 || sleep == -1)
	{
		printf("Error: Invalid arguments (non-numeric or out of range)\n");
		return (0);
	}
	if (philos <= 0 || philos >= 200)
	{
		printf("Error: the program only allows between 1 and 199 philosophers\n");
		return (0);
	}
	if (die < 60 || eat < 60 || sleep < 60)
	{
		printf("Error: time values must be at least 60ms\n");
		return (0);
	}
	return (1);
}
