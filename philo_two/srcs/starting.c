/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 20:34:08 by gselyse           #+#    #+#             */
/*   Updated: 2021/02/10 15:39:38 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static void		loop(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_message(philo, 1);
	sem_wait(philo->data->forks);
	print_message(philo, 1);
	eat(philo);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void			*life(void *argv)
{
	t_philo		*philo;
	int			count;

	count = 2;
	philo = argv;
	philo->time_last_eat = get_time();
	while (!g_stop)
	{
		loop(philo);
		if (philo->data->must_eat > 0)
		{
			if (philo->count_eat >= philo->data->must_eat)
				count++;
			if (count == philo->data->num_philo)
			{
				print_message(philo, 6);
				break ;
			}
		}
		print_message(philo, 3);
		usleep(philo->data->time_to_sleep * 1000);
		print_message(philo, 4);
	}
	return (NULL);
}

void			eat(t_philo *philo)
{
	print_message(philo, 2);
	philo->time_last_eat = get_time();
	sem_wait(philo->eat_philo);
	usleep(philo->data->time_to_eat * 1000);
	philo->count_eat++;
	sem_post(philo->eat_philo);
}
