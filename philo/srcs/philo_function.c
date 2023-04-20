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
		print_message(watcher, philo, FORK);
	}
	else if (philo->philo_num % 2 == 1)
	{
		pthread_mutex_lock(&watcher->fork[(philo->philo_num + 1) \
		% watcher->num_of_philo]);
		print_message(watcher, philo, FORK);
		pthread_mutex_lock(&watcher->fork[philo->philo_num]);
		print_message(watcher, philo, FORK);
	}
	philo->last_eat = get_current_time(watcher);
	print_message(watcher, philo, EAT);
	usleep(watcher->time_to_eat);
	pthread_mutex_unlock(&watcher->fork[philo->philo_num]);
	pthread_mutex_unlock(&watcher->fork[(philo->philo_num + 1) \
	% watcher->num_of_philo]);
	philo->num_of_eat++;
}

void	sleep_and_think(t_watcher *watcher, t_philo *philo)
{
	print_message(watcher, philo, SLEEP);
	usleep(watcher->time_to_sleep);
	if (watcher->time_to_eat - watcher->time_to_sleep > 0)
	{
		print_message(watcher, philo, THINK);
		usleep(watcher->time_to_eat - watcher->time_to_sleep);
	}
}

void	*philo_function(void *arg)
{
	t_watcher	*watcher;
	t_philo		*philo;

	watcher = (t_watcher *)arg;
	philo = watcher->philo_info[watcher->philo_num];
	init_philo(watcher, philo);
	pthread_mutex_lock(&watcher->lock);
	pthread_mutex_unlock(&watcher->lock);
	philo->last_eat = watcher->start_time.tv_usec;
	while (philo->is_full == 0 && philo->is_died == 0)
	{
		if (philo->is_full == 0 && philo->is_died == 0)
			get_fork_and_eat(watcher, philo);
		if (philo->num_of_eat == watcher->max_eating)
		{
			philo->is_full = 1;
			break ;
		}
		if (philo->is_full == 0 && philo->is_died == 0)
			sleep_and_think(watcher, philo);
	}
	return (0);
}
