/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberthod <bberthod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 14:23:34 by blandineber       #+#    #+#             */
/*   Updated: 2023/09/21 12:51:38 by bberthod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine_one(t_philo *philo)
{
	philo->last_meal = philo->data->start;
	pthread_mutex_lock(philo->l_fork);
	if (check_philo(philo) == DEATH)
	{
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	if (ft_print(philo, "has taken a fork") == DEATH)
	{
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	if (ft_waiting(philo, philo->data->die + 5) == DEATH)
	{
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
}

void	routine_count(t_philo *philo)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	philo->last_meal = philo->data->start;
	while (i < philo->data->nb_meals)
	{
		if (i == philo->data->nb_meals - 1)
			flag = 1;
		if (philo->id % 2 == 0)
		{
			if (take_fork_pair(philo, flag) == DEATH)
				break ;
		}
		else
		{
			if (take_fork_impair(philo, flag) == DEATH)
				break ;
		}
		i++;
	}
}

void	routine_no_count(t_philo *philo)
{
	philo->last_meal = philo->data->start;
	while (1)
	{
		if (philo->id % 2 == 0)
		{
			if (take_fork_pair(philo, 0) == DEATH)
				break ;
		}
		else
		{
			if (take_fork_impair(philo, 0) == DEATH)
				break ;
		}
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (get_time() < philo->data->start)
		usleep(200);
	if (philo->data->nb_philo == 1)
		routine_one(philo);
	{
		if (philo->data->nb_meals > 0)
			routine_count(philo);
		else
			routine_no_count(philo);
	}
	return (NULL);
}

int	threads_philo(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	data->start = get_time() + 2000;
	while (i < data->nb_philo)
	{
		if (pthread_create(&philo[i].t_id, NULL, routine,
				(void *)&philo[i]) != 0)
			return (FAIL);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(philo[i].t_id, NULL);
		i++;
	}
	return (SUCCESS);
}
