/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 20:34:08 by gselyse           #+#    #+#             */
/*   Updated: 2021/02/09 23:39:06 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int			life(t_philo *philo)
{
	pthread_t	thread;

	philo->time_last_eat = get_time();
	if (pthread_create(&thread, NULL, &wait_end, (void *)philo))
		return (EXIT_FAILURE);
	pthread_detach(thread);
	while (1)
	{
		sem_wait(philo->data->forks);
		print_message(philo, 1);
		sem_wait(philo->data->forks);
		print_message(philo, 1);
		eat(philo);
		sem_post(philo->data->forks);
		sem_post(philo->data->forks);
		print_message(philo, 3);
		usleep(philo->data->time_to_sleep * 1000);
		print_message(philo, 4);
	}
	return (EXIT_SUCCESS);
}

void		eat(t_philo *philo)
{
	print_message(philo, 2);
	philo->time_last_eat = get_time();
	sem_wait(philo->eat_philo);
	usleep(philo->data->time_to_eat * 1000);
	philo->count_eat++;
	sem_post(philo->eat_philo);
	sem_post(philo->count_sem);
}
