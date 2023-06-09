/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_watcher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 02:32:09 by marvin            #+#    #+#             */
/*   Updated: 2023/04/07 02:32:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/philosopher.h"

void	initialize_watcher_1(char **argv, t_watcher *watcher)
{
	int	i;

	i = 0;
	if (gettimeofday(&watcher->start_time, 0) == -1)
		error_exit("gettimeofday error", watcher);
	watcher->num_of_philo = ft_atoi(argv[1]);
	watcher->time_to_die = ft_atoi(argv[2]);
	watcher->time_to_eat = ft_atoi(argv[3]);
	watcher->time_to_sleep = ft_atoi(argv[4]);
	watcher->someone_died = 0;
	watcher->start_eating = 0;
	if (watcher->max_eating != -1)
		watcher->max_eating = ft_atoi(argv[5]);
	watcher->philo_info = malloc(watcher->num_of_philo * sizeof(t_philo *));
	if (watcher->philo_info == 0)
		error_exit("malloc fail: ", watcher);
	while (i < watcher->num_of_philo)
	{
		watcher->philo_info[i] = malloc(sizeof(t_philo));
		if (watcher->philo_info[i] == 0)
			error_exit("malloc fail: ", watcher);
		i++;
	}
	initialize_watcher_2(watcher);
}

void	initialize_watcher_2(t_watcher *watcher)
{
	int	i;

	i = 0;
	watcher->philo_id = malloc(watcher->num_of_philo * sizeof(pthread_t));
	if (watcher->philo_id == 0)
		error_exit("malloc fail: ", watcher);
	watcher->fork = malloc(watcher->num_of_philo * sizeof(pthread_mutex_t));
	if (watcher->fork == 0)
		error_exit("malloc fail: ", watcher);
	if (pthread_mutex_init(&watcher->print_lock, NULL) == -1)
		error_exit("mutex_init_fail: ", watcher);
	if (pthread_mutex_init(&watcher->start_lock, NULL) == -1)
		error_exit("mutex_init_fail: ", watcher);
	if (pthread_mutex_init(&watcher->time_lock, NULL) == -1)
		error_exit("mutex_init_fail: ", watcher);
	if (pthread_mutex_init(&watcher->lasteat_lock, NULL) == -1)
		error_exit("mutex_init_fail: ", watcher);
	if (pthread_mutex_init(&watcher->die_lock, NULL) == -1)
		error_exit("mutex_init_fail: ", watcher);
	if (pthread_mutex_init(&watcher->full_lock, NULL) == -1)
		error_exit("mutex_init_fail: ", watcher);
	while (i < watcher->num_of_philo)
		if (pthread_mutex_init(&watcher->fork[i++], NULL) == -1)
			error_exit("mutex_init_fail: ", watcher);
}
