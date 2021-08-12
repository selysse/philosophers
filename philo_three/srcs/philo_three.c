/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 17:09:01 by gselyse           #+#    #+#             */
/*   Updated: 2021/02/11 13:50:39 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void		*wait_end(void *argv)
{
	t_philo	*philo;

	philo = argv;
	while (g_stop)
	{
		sem_wait(philo->eat_philo);
		if (get_time() - philo->time_last_eat > philo->data->time_to_die)
		{
			g_stop = 0;
			print_message(philo, 5);
		}
		sem_post(philo->eat_philo);
		usleep(100);
	}
	return (NULL);
}

static int	loop(t_data *data)
{
	int			i;

	i = 0;
	while (i < data->num_philo)
	{
		if (!(data->philo[i].pid = fork()))
			life(&data->philo[i]);
		else if (data->philo[i].pid < 0)
			return (EXIT_FAILURE);
		usleep(1000);
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	start(t_data *data)
{
	int			i;
	int			count;

	count = 0;
	data->start_time = get_time();
	loop(data);
	if (data->must_eat > 0)
	{
		if (!(data->count = fork()))
		{
			while (count < data->must_eat)
			{
				i = 0;
				while (i < data->num_philo)
					sem_wait(data->philo[i++].count_sem);
				count++;
			}
			print_message(&data->philo[0], 6);
		}
	}
	waitpid(-1, NULL, 0);
	return (EXIT_SUCCESS);
}

int			main(int argc, char **argv)
{
	t_data	data;

	g_stop = 1;
	memset(&data, 0, sizeof(t_data));
	sem_unlink("forks");
	sem_unlink("write");
	if (ft_parsing(&data, argc, argv) == 1)
	{
		free_philo(&data);
		return (EXIT_FAILURE);
	}
	if (start(&data) == 1)
	{
		free_philo(&data);
		return (EXIT_FAILURE);
	}
	free_philo(&data);
	return (EXIT_SUCCESS);
}
