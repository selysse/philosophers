/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 18:48:33 by gselyse           #+#    #+#             */
/*   Updated: 2021/02/09 14:54:29 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int		check(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("%s\n", "Wrong arguments");
		return (1);
	}
	if (numbers(argc, argv))
	{
		printf("%s\n", "Arguments must be positive numbers.");
		return (1);
	}
	if (ft_atoi(argv[1]) < 2 || ft_atoi(argv[1]) > 200)
	{
		printf("%s\n", "At least 2 philosophers are requered.");
		return (1);
	}
	if (argc == 6)
	{
		if (ft_atoi(argv[5]) < 1)
		{
			printf("%s\n", "Philosophers can't eat 0 times.");
			return (1);
		}
	}
	return (0);
}

static int		init_philo(t_data *data)
{
	int i;

	i = 0;
	while (i < data->num_philo)
	{
		data->philo[i].index = i;
		data->philo[i].count_eat = 0;
		data->philo[i].l_fork = i;
		data->philo[i].r_fork = (i + 1) % data->num_philo;
		pthread_mutex_init(&data->philo[i].eat_philo, NULL);
		data->philo[i].data = data;
		i++;
	}
	if (!(data->forks = malloc(sizeof(t_data) * data->num_philo)))
		return (EXIT_FAILURE);
	i = 0;
	while (i < data->num_philo)
		pthread_mutex_init(&data->forks[i++], NULL);
	pthread_mutex_init(&data->write, NULL);
	return (EXIT_SUCCESS);
}

int				ft_parsing(t_data *data, int argc, char **argv)
{
	if (check(argc, argv) == 1)
		return (EXIT_FAILURE);
	data->num_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	else
		data->must_eat = -1;
	if (!(data->philo = malloc(sizeof(t_data) * data->num_philo)))
		return (EXIT_FAILURE);
	init_philo(data);
	return (EXIT_SUCCESS);
}
