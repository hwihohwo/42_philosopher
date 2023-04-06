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
	watcher->num_of_philo = ft_atoi(argv[1]);
	watcher->time_to_die = ft_atoi(argv[2]);
	watcher->time_to_eat = ft_atoi(argv[3]);
	watcher->time_to_sleep = ft_atoi(argv[4]);
	if (gettimeofday(&watcher->start_time, NULL) == -1)
		error_exit("gettimeofday: ", watcher);
	if (watcher->max_eating != -1)
		watcher->max_eating = ft_atoi(argv[5]);
	watcher->philo_info = calloc(1, sizeof(t_philo *));
	if (watcher->philo_info == 0)
		error_exit("malloc fail: ", watcher);
	while (i < watcher->num_of_philo)
	{
		watcher->philo_info[i] = calloc(1, sizeof(t_philo));
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
	watcher->philo_id = calloc(watcher->num_of_philo, sizeof(pthread_t));
	if (watcher->philo_id == 0)
		error_exit("malloc fail: ", watcher);
	watcher->fork = calloc(watcher->num_of_philo, sizeof(pthread_mutex_t));
	if (watcher->fork == 0)
		error_exit("malloc fail: ", watcher);
	if (pthread_mutex_init(&watcher->lock) == -1)
		error_exit("mutex_init_fail: ", watcher);
	while (i < num_of_philo)
		if (pthread_mutex_init(&watcher->fork[i++]) == -1)
			error_exit("mutex_init_fail: ", watcher);
}
