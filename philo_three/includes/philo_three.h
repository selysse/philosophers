/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gselyse <gselyse@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:54:18 by gselyse           #+#    #+#             */
/*   Updated: 2021/02/11 13:50:25 by gselyse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <fcntl.h>
# include <semaphore.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

# define EAT	" is eating\n"
# define SLEAP	" is sleeping\n"
# define FORK	" has taken a fork\n"
# define THINK	" is thinking\n"
# define DIED	" has died\n"
# define FULL	" the simulation is over\n"

int		g_stop;

typedef struct		s_philo
{
	int				index;
	int				time_last_eat;
	int				count_eat;
	sem_t			*eat_philo;
	sem_t			*count_sem;
	pid_t			pid;
	struct s_data	*data;
}					t_philo;

typedef struct		s_data
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				start_time;
	t_philo			*philo;
	sem_t			*forks;
	sem_t			*write;
	pid_t			count;
}					t_data;

int					ft_atoi(const char *str);
int					ft_strlen(char *str);
int					get_time(void);
int					numbers(int nb, char **str);
void				print_message(t_philo *philo, int n);
int					ft_parsing(t_data *data, int argc, char **argv);
int					life(t_philo *philo);
void				*wait_end(void *argv);
void				eat(t_philo *ph);
void				free_philo(t_data *data);
char				*ft_strdup(char *str);

#endif
