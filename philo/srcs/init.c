/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberthod <bberthod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:36:53 by blandineber       #+#    #+#             */
/*   Updated: 2023/09/21 13:56:20 by bberthod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, int argc, char **argv)
{
	data->nb_philo = ft_atoi(argv[1]);
	data->die = ft_atoi(argv[2]);
	data->eat = ft_atoi(argv[3]);
	data->sleep = ft_atoi(argv[4]);
	if (data->eat > data->sleep)
		data->max = data->eat;
	else
		data->max = data->sleep;
	if (data->nb_philo % 2 == 0 || data->die >= 3 * data->max)
		data->think = data->eat - data->sleep + 3;
	else
		data->think = 0;
	data->dead = 0;
	if (argc == 6)
		data->nb_meals = ft_atoi(argv[5]);
	else
		data->nb_meals = -1;
	return (SUCCESS);
}

void	destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->death);
	pthread_mutex_destroy(&data->print);
	free(data->forks);
}

int	init_mutex(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&data->death, NULL))
		return (FAIL);
	if (pthread_mutex_init(&data->print, NULL))
		return (FAIL);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (FAIL);
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

int	init_philo(t_data *data)
{
	int	i;
	int	j;

	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philo)
		return (FAIL);
	i = 0;
	j = 1;
	while (i < data->nb_philo)
	{
		data->philo[i].last_meal = 0;
		data->philo[i].id = j;
		data->philo[i].l_fork = &data->forks[i];
		data->philo[i].r_fork = &data->forks[(i + 1) % data->nb_philo];
		data->philo[i].data = data;
		i++;
		j++;
	}
	return (SUCCESS);
}
