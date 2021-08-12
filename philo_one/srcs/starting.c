/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 20:34:08 by gselyse           #+#    #+#             */
/*   Updated: 2021/02/09 14:59:30 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void		loop(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->l_fork]);
	print_message(philo, 1);
	pthread_mutex_lock(&philo->data->forks[philo->r_fork]);
	print_message(philo, 1);
	eat(philo);
	pthread_mutex_unlock(&philo->data->forks[philo->l_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->r_fork]);
}

void			*life(void *argv)
{
	t_philo		*philo;
	int			count;

	count = 3;
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
	pthread_mutex_lock(&philo->eat_philo);
	usleep(philo->data->time_to_eat * 1000);
	philo->count_eat++;
	pthread_mutex_unlock(&philo->eat_philo);
}
