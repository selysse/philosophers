/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 17:09:01 by gselyse           #+#    #+#             */
/*   Updated: 2021/02/10 15:37:05 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void		free_philo(t_data *data)
{
	int i;

	i = 0;
	if (data)
	{
		if (data->philo)
		{
			while (i < data->num_philo)
			{
				sem_unlink(data->philo[i].sem);
				free(data->philo[i].sem);
				data->philo[i].sem = NULL;
				i++;
			}
			free(data->philo);
			data->philo = NULL;
		}
		sem_unlink("/forks");
		sem_unlink("/write");
	}
}

void		*wait_end(void *argv)
{
	t_philo	*philo;

	philo = argv;
	while (!g_stop)
	{
		sem_wait(philo->eat_philo);
		if (!g_stop && \
		get_time() - philo->time_last_eat > philo->data->time_to_die)
		{
			print_message(philo, 5);
			sem_post(philo->eat_philo);
			return (NULL);
		}
		sem_post(philo->eat_philo);
		usleep(1000);
	}
	return (NULL);
}

static int	start(t_data *data)
{
	int			i;
	pthread_t	thread;

	i = 0;
	data->start_time = get_time();
	while (i < data->num_philo)
	{
		data->philo[i].time_last_eat = get_time();
		if (pthread_create(&thread, NULL, &life, \
		&data->philo[i]))
			return (EXIT_FAILURE);
		pthread_detach(thread);
		if (pthread_create(&data->philo[i].thrd, NULL, &wait_end, \
		(void*)&data->philo[i]))
			return (EXIT_FAILURE);
		usleep(1000);
		i++;
	}
	i = 0;
	while (i < data->num_philo)
		pthread_join(data->philo[i++].thrd, NULL);
	return (EXIT_SUCCESS);
}

int			main(int argc, char **argv)
{
	t_data	data;

	g_stop = 0;
	memset(&data, 0, sizeof(t_data));
	sem_unlink("/forks");
	sem_unlink("/write");
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
	return (0);
}
