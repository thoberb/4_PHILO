/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberthod <bberthod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:18:10 by bberthod          #+#    #+#             */
/*   Updated: 2023/09/19 18:40:40 by bberthod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlock_forks_r_l(t_philo *philo)
{
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	unlock_forks_l_r(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

int	check_all(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death);
	if (philo->data->dead == 1)
		return (pthread_mutex_unlock(&philo->data->death), DEATH);
	pthread_mutex_unlock(&philo->data->death);
	return (SUCCESS);
}

int	check_philo(t_philo *philo)
{
	if ((get_time() - philo->last_meal) >= philo->data->die)
	{
		pthread_mutex_lock(&philo->data->death);
		if (philo->data->dead == 1)
			return (pthread_mutex_unlock(&philo->data->death), DEATH);
		else
		{
			philo->data->dead = 1;
			pthread_mutex_unlock(&philo->data->death);
			pthread_mutex_lock(&philo->data->print);
			printf("%ld %d %s\n", get_running_time(philo), philo->id, "died");
			pthread_mutex_unlock(&philo->data->print);
			return (DEATH);
		}
	}
	return (SUCCESS);
}
