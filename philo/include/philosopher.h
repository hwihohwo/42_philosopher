/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:08:35 by marvin            #+#    #+#             */
/*   Updated: 2023/03/27 19:08:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

enum e_philostate
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE
};

typedef struct s_philo
{
	int	philo_num;
	int	last_eat;
	int	num_of_eat;
	int	is_died;
	int	is_full;
}	t_philo;

typedef struct s_watcher
{
	int				num_of_philo;
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eating;
	struct timeval	start_time;
	struct timeval	current_time;
	t_philo			**philo_info;
	pthread_t		*philo_id;
	pthread_mutex_t	*fork;
	pthread_mutex_t	lock;
}	t_watcher;

//philo_utils.c
void	free_watcher(t_watcher *watcher);
void	error_exit(char *str, t_watcher *watcher);
int		get_current_time(t_watcher *watcher);
void	print_message(t_watcher *watcher, t_philo *philo, int state);
int		ft_atoi(char *str);

//initialize_watcher.c
void	initialize_watcher_1(char **argv, t_watcher *watcher);
void	initialize_watcher_2(t_watcher *watcher);\

//check_philo.c
int		create_philo(t_watcher *watcher);
void	philo_died(t_watcher *watcher, int philo_num);
void	philo_finished(t_watcher *watcher);
int		watch_philo(t_watcher *watcher);

//philo_function.c
void	init_philo(t_watcher *watcher, t_philo *philo);
void	get_fork_and_eat(t_watcher *watcher, t_philo *philo);
void	sleep_and_think(t_watcher *watcher, t_philo *philo);
void	*philo_function(void *arg);

#endif