/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 17:09:01 by gselyse           #+#    #+#             */
/*   Updated: 2021/02/09 15:12:03 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void		free_philo(t_data *data)
{
	int i;

	i = 0;
	if (data)
	{
		if (data->forks)
		{
			while (i < data->num_philo)
				pthread_mutex_destroy(&data->forks[i++]);
			free(data->forks);
		}
		pthread_mutex_destroy(&data->write);
		if (data->philo)
		{
			i = 0;
			while (i < data->num_philo)
				pthread_mutex_destroy(&data->philo[i++].eat_philo);
			free(data->philo);
			data->philo = NULL;
		}
	}
}

void		*wait_end(void *argv)
{
	t_philo	*philo;

	philo = argv;
	while (!g_stop)
	{
		pthread_mutex_lock(&philo->eat_philo);
		if (!g_stop && \
		get_time() - philo->time_last_eat > philo->data->time_to_die)
		{
			print_message(philo, 5);
			pthread_mutex_unlock(&philo->eat_philo);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->eat_philo);
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
		if (pthread_create(&thread, NULL, life, \
		(void*)&data->philo[i]))
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
