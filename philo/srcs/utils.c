/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberthod <bberthod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 16:26:43 by blandineber       #+#    #+#             */
/*   Updated: 2023/09/20 19:00:32 by bberthod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_print(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->print);
	if (check_all(philo) == DEATH)
		return (pthread_mutex_unlock(&philo->data->print), DEATH);
	printf("%ld %d %s\n", get_running_time(philo), philo->id, msg);
	pthread_mutex_unlock(&philo->data->print);
	return (SUCCESS);
}

long	get_time(void)
{
	struct timeval	time;
	long			ms;

	if (gettimeofday(&time, NULL) < 0)
		return (0);
	ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (ms);
}

long	get_running_time(t_philo *philo)
{
	long	time;

	time = get_time();
	return (time - philo->data->start);
}

int	ft_waiting(t_philo *philo, long time)
{
	long	start;

	start = get_time();
	while (get_time() - start < time)
	{
		if (check_philo(philo) == DEATH)
			return (DEATH);
		usleep(200);
	}
	return (SUCCESS);
}

int	ft_atoi(char *str)
{
	int	i;
	int	signe;
	int	res;

	i = 0;
	res = 0;
	signe = 1;
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
		i++;
	while (str[i] && str[i] == '+')
			i++;
	if (str[i] == '-')
	{
		signe = -1;
		i++;
	}
	while (str[i])
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * signe);
}
