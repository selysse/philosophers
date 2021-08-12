/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 18:48:33 by gselyse           #+#    #+#             */
/*   Updated: 2021/02/10 15:44:43 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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

static char		*ft_strdup(char *str)
{
	char	*new;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(str);
	new = (char *)malloc((sizeof(char) * (len + 1)));
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

static int		create_sem(t_philo *philo)
{
	if (!(philo->sem = ft_strdup("eat_philo")))
		return (1);
	sem_unlink(philo->sem);
	if ((philo->eat_philo = sem_open(philo->sem, O_CREAT, 0644, 1)) \
	== SEM_FAILED)
		return (1);
	return (0);
}

static int		init_philo(t_data *data)
{
	int i;

	i = 0;
	while (i < data->num_philo)
	{
		memset(&data->philo[i], 0, sizeof(t_philo));
		data->philo[i].index = i;
		data->philo[i].count_eat = 0;
		data->philo[i].data = data;
		if (create_sem(&data->philo[i]))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int				ft_parsing(t_data *data, int argc, char **argv)
{
	if (check(argc, argv) == 1)
		return (1);
	data->num_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	else
		data->must_eat = -1;
	if (!(data->philo = malloc(sizeof(t_data) * data->num_philo)))
		return (1);
	if (init_philo(data))
		return (EXIT_FAILURE);
	if ((data->forks = sem_open("/forks", O_CREAT, 0660, data->num_philo)) \
	== SEM_FAILED)
		return (1);
	if ((data->write = sem_open("/write", O_CREAT, 0660, 1)) == SEM_FAILED)
		return (1);
	return (0);
}
