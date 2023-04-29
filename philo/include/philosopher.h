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
	int					philo_num;
	int					last_eat;
	int					num_of_eat;
	int					is_full;
	struct s_watcher	*watcher;
}	t_philo;

typedef struct s_watcher
{
	int				num_of_philo;
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eating;
	int				start_eating;
	int				someone_died;
	struct timeval	start_time;
	struct timeval	current_time;
	t_philo			**philo_info;
	pthread_t		*philo_id;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	start_lock;
	pthread_mutex_t	time_lock;
	pthread_mutex_t	lasteat_lock;
	pthread_mutex_t	die_lock;
	pthread_mutex_t	full_lock;
}	t_watcher;

//philo_utils_1.c
void	free_watcher(t_watcher *watcher);
void	error_exit(char *str, t_watcher *watcher);
int		get_current_time(t_watcher *watcher);
void	print_message(t_watcher *watcher, t_philo *philo, int state);
int		ft_atoi(char *str);

//philo_utils_2.c
void	change_last_eat(t_watcher *watcher, int philo_num, int value);
int		get_last_eat(t_watcher *watcher, int philo_num);
void	change_someone_died(t_watcher *watcher);
int		get_someone_died(t_watcher *watcher);

//philo_utils_3.c
void	change_is_full(t_watcher *watcher, int philo_num);
int		get_is_full(t_watcher *watcher, int philo_num);

//initialize_watcher.c
void	initialize_watcher_1(char **argv, t_watcher *watcher);
void	initialize_watcher_2(t_watcher *watcher);

//check_philo.c
int		create_philo(t_watcher *watcher);
void	philo_died(t_watcher *watcher, int philo_num);
void	philo_finished(t_watcher *watcher);
void	watch_philo(t_watcher *watcher);

//philo_function.c
void	init_philo(t_watcher *watcher, t_philo *philo);
void	get_fork_and_eat(t_watcher *watcher, t_philo *philo);
void	sleep_and_think(t_watcher *watcher, t_philo *philo);
void	*philo_function(void *arg);
void	ft_usleep(t_watcher *watcher, int milsec);

#endif