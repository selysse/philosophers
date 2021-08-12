/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 20:27:47 by gselyse           #+#    #+#             */
/*   Updated: 2021/02/11 13:37:08 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void	philo_kill(t_data *data)
{
	int i;

	i = 0;
	if (data)
	{
		sem_unlink("forks");
		sem_unlink("write");
		if (data->must_eat > 0)
			kill(data->count, SIGKILL);
		if (data->philo)
		{
			while (i < data->num_philo)
				kill(data->philo[i++].pid, SIGKILL);
		}
	}
}

void		free_philo(t_data *data)
{
	char	*name;
	int		i;

	i = 0;
	name = NULL;
	if (data)
	{
		philo_kill(data);
		while (i < data->num_philo)
		{
			name = ft_strdup("eat_philo");
			sem_unlink(name);
			free(name);
			name = NULL;
			name = ft_strdup("count_sem");
			sem_unlink(name);
			free(name);
			name = NULL;
			i++;
		}
		free(data->philo);
	}
}
