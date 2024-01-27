/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberthod <bberthod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:42:16 by bberthod          #+#    #+#             */
/*   Updated: 2023/09/21 13:48:55 by bberthod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	checkintmax(char *str)
{
	int	i;

	i = 0;
	if (strlen(str) > strlen("2147483647"))
		return (FAIL);
	if (strlen(str) < strlen("2147483647"))
		return (SUCCESS);
	while (i < ft_strlen(str))
	{
		if (str[i] > "2147483647"[i])
			return (FAIL);
		else if (str[i] < "2147483647"[i])
			return (SUCCESS);
		i++;
	}
	return (SUCCESS);
}

int	checkint(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == '+')
			{
				while (argv[i][j] && (argv[i][j] == '+'))
					j++;
			}
			if (checkintmax(&argv[i][j]) == FAIL)
				return (FAIL);
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (FAIL);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	errorcheck(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (FAIL);
	if (checkint(argc, argv) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(data));
	if (errorcheck(argc, argv) == FAIL)
		return (FAIL);
	if (init_data(&data, argc, argv) == FAIL)
		return (FAIL);
	if (init_mutex(&data) == FAIL)
		return (destroy_mutex(&data), FAIL);
	if (init_philo(&data) == FAIL)
		return (destroy_mutex(&data), FAIL);
	threads_philo(&data, data.philo);
	destroy_mutex(&data);
	free(data.philo);
	return (SUCCESS);
}
