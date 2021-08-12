/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:26:01 by gselyse           #+#    #+#             */
/*   Updated: 2021/02/09 15:05:02 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int			get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

static void	print_status(int n)
{
	if (n == 1)
		printf("%s", FORK);
	else if (n == 2)
		printf("%s", EAT);
	else if (n == 3)
		printf("%s", SLEAP);
	else if (n == 4)
		printf("%s", THINK);
	else if (n == 5)
		printf("%s", DIED);
	else if (n == 6)
		printf("%s", FULL);
}

void		print_message(t_philo *philo, int n)
{
	int	time;

	pthread_mutex_lock(&philo->data->write);
	if (!g_stop)
	{
		time = get_time() - philo->data->start_time;
		printf("%d", time);
		if (n != 6)
			printf("%s%d", " ", philo->index + 1);
		print_status(n);
		if (n == 5 || n == 6)
		{
			g_stop = 1;
			return ;
		}
	}
	pthread_mutex_unlock(&philo->data->write);
}
