/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberthod <bberthod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:45:36 by bberthod          #+#    #+#             */
/*   Updated: 2023/09/21 14:23:50 by bberthod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_sleep(t_philo *philo)
{
	if (ft_print(philo, "is sleeping") == DEATH)
		return (DEATH);
	if (ft_waiting(philo, philo->data->sleep) == DEATH)
		return (DEATH);
	if (ft_print(philo, "is thinking") == DEATH)
		return (DEATH);
	if (ft_waiting(philo, philo->data->think) == DEATH)
		return (DEATH);
	return (SUCCESS);
}

int	ft_eat_pair(t_philo *philo, int flag)
{
	if (ft_print(philo, "is eating") == DEATH)
		return (unlock_forks_r_l(philo), DEATH);
	if (philo->data->sleep > philo->data->die
		|| philo->data->sleep > philo->data->die)
		philo->last_meal = get_time();
	if (ft_waiting(philo, philo->data->eat) == DEATH)
		return (unlock_forks_r_l(philo), DEATH);
	unlock_forks_r_l(philo);
	if (philo->data->sleep <= philo->data->die
		&& philo->data->sleep <= philo->data->die)
		philo->last_meal = get_time();
	if (flag == 1)
		return (SUCCESS);
	if (ft_sleep(philo) == DEATH)
		return (DEATH);
	return (SUCCESS);
}

int	ft_eat_impair(t_philo *philo, int flag)
{
	if (ft_print(philo, "is eating") == DEATH)
		return (unlock_forks_l_r(philo), DEATH);
	if (philo->data->sleep > philo->data->die
		|| philo->data->sleep > philo->data->die)
		philo->last_meal = get_time();
	if (ft_waiting(philo, philo->data->eat) == DEATH)
		return (unlock_forks_l_r(philo), DEATH);
	unlock_forks_l_r(philo);
	if (philo->data->sleep <= philo->data->die
		&& philo->data->sleep <= philo->data->die)
		philo->last_meal = get_time();
	if (flag == 1)
		return (SUCCESS);
	if (ft_sleep(philo) == DEATH)
		return (DEATH);
	return (SUCCESS);
}

int	take_fork_pair(t_philo *philo, int flag)
{
	pthread_mutex_lock(philo->l_fork);
	if (check_philo(philo) == DEATH)
	{
		pthread_mutex_unlock(philo->l_fork);
		return (DEATH);
	}
	if (ft_print(philo, "has taken a fork") == DEATH)
	{
		pthread_mutex_unlock(philo->l_fork);
		return (DEATH);
	}
	pthread_mutex_lock(philo->r_fork);
	if (check_philo(philo) == DEATH)
		return (unlock_forks_r_l(philo), DEATH);
	if (ft_print(philo, "has taken a fork") == DEATH)
		return (unlock_forks_r_l(philo), DEATH);
	if (ft_eat_pair(philo, flag) == DEATH)
		return (DEATH);
	return (SUCCESS);
}

int	take_fork_impair(t_philo *philo, int flag)
{
	usleep(500);
	pthread_mutex_lock(philo->r_fork);
	if (check_philo(philo) == DEATH)
	{
		pthread_mutex_unlock(philo->r_fork);
		return (DEATH);
	}
	if (ft_print(philo, "has taken a fork") == DEATH)
	{
		pthread_mutex_unlock(philo->r_fork);
		return (DEATH);
	}
	pthread_mutex_lock(philo->l_fork);
	if (check_philo(philo) == DEATH)
		return (unlock_forks_l_r(philo), DEATH);
	if (ft_print(philo, "has taken a fork") == DEATH)
		return (unlock_forks_l_r(philo), DEATH);
	if (ft_eat_impair(philo, flag) == DEATH)
		return (DEATH);
	return (SUCCESS);
}
