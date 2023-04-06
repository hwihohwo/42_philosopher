/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:23:19 by marvin            #+#    #+#             */
/*   Updated: 2023/03/30 17:23:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/philosopher.h"

void	init_philo(t_watcher *watcher, t_philo *philo)
{
	philo->philo_num = watcher->philo_num;
	philo->last_eat = 0;
	philo->num_of_eat = 0;
	philo->is_died = 0;
	philo->is_full = 0;
}

void	get_fork_and_eat(t_watcher *watcher, t_philo *philo)
{
	if (philo->philo_num % 2 == 0)
	{
		pthread_mutex_lock(&watcher->fork[philo->philo_num]);
		print_message(watcher, philo, FORK);
		pthread_mutex_lock(&watcher->fork[(philo->philo_num + 1) \
		% watcher->num_of_philo]);

	}
	else if (philo->philo_num % 2 == 1)
	{
		pthread_mutex_lock(&watcher->fork[(philo->philo_num + 1) \
		% watcher->num_of_philo]);
		print_message(watcher, philo, FORK);
		pthread_mutex_lock(&watcher->fork[philo->philo_num]);
	}
	print_message(watcher, philo, EAT);
	philo->last_eat = get_current_time(watcher);
	usleep(watcher->time_to_eat);
	pthread_mutex_unlock(&watcher->fork[philo->philo_num]);
	pthread_mutex_unlock(&watcher->fork[(philo->philo_num + 1) \
	% watcher->num_of_philo]);
}

void	*philo_function(void *arg)
{
	t_watcher	*watcher;
	t_philo		*philo;

	watcher = (t_watcher *)arg;
	philo = &watcher->philo_info[philo_num];
	init_philo(watcher, philo);
	pthread_mutex_lock(&watcher->lock);
	pthread_mutex_unlock(&watcher->lock);
	while (philo->is_full == 0 && philo->is_died == 0)
	{
		get_fork_and_eat(watcher, philo);
		philo->num_of_eat++;
		if (philo->num_of_eat == watcher->max_eating)
			philo->is_full = 1;
		print_message(watcher, philo, SLEEP);
		usleep(watcher->time_to_sleep);
	}
}
