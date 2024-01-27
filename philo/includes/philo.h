/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberthod <bberthod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 16:02:16 by blandineber       #+#    #+#             */
/*   Updated: 2023/09/20 17:31:26 by bberthod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define SUCCESS 0
# define FAIL 1
# define DEATH 3

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_t		t_id;
	long			last_meal;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	long			start;
	long			die;
	long			eat;
	long			sleep;
	long			think;
	long			max;
	int				nb_philo;
	int				nb_meals;
	int				dead;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
	pthread_mutex_t	*forks;
	t_philo			*philo;
}				t_data;

//-------------DEATH----------------
void	unlock_forks_l_r(t_philo *philo);
void	unlock_forks_r_l(t_philo *philo);
int		check_all(t_philo *philo);
int		check_philo(t_philo *philo);

//-------------EST_SLEEP------------
int		ft_sleep(t_philo *philo);
int		ft_eat_pair(t_philo *philo, int flag);
int		ft_eat_impair(t_philo *philo, int flag);
int		take_fork_pair(t_philo *philo, int flag);
int		take_fork_impair(t_philo *philo, int flag);

//-------------INIT-----------------
int		init_data(t_data *data, int argc, char **argv);
void	destroy_mutex(t_data *data);
int		init_mutex(t_data *data);
int		init_philo(t_data *data);

//-------------THREADS--------------
void	routine_count(t_philo *philo);
void	routine_no_count(t_philo *philo);
void	*routine(void *arg);
int		threads_philo(t_data *data, t_philo *philo);

//-------------UTILS----------------
int		ft_print(t_philo *philo, char *msg);
long	get_time(void);
long	get_running_time(t_philo *philo);
int		ft_waiting(t_philo *philo, long time);
int		ft_atoi(char *str);

#endif
