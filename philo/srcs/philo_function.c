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

void	ft_usleep(t_watcher *watcher, int milsec)
{
	int	dest;

	dest = get_current_time(watcher) + milsec;
	while (dest > get_current_time(watcher))
		usleep(milsec);
}

void	init_philo(t_watcher *watcher, t_philo *philo)
{
	philo->philo_num = watcher->philo_num;
	philo->num_of_eat = 0;
	philo->is_full = 0;
	philo->is_died = 0;
	philo->last_eat = get_current_time(watcher);
	philo->watcher = watcher;
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
	ft_usleep(watcher, watcher->time_to_eat);
	pthread_mutex_unlock(&watcher->fork[philo->philo_num]);
	pthread_mutex_unlock(&watcher->fork[(philo->philo_num + 1) \
	% watcher->num_of_philo]);
	philo->num_of_eat++;
}

void	sleep_and_think(t_watcher *watcher, t_philo *philo)
{
	print_message(watcher, philo, SLEEP);
	ft_usleep(watcher, watcher->time_to_sleep);
	if (watcher->time_to_eat - watcher->time_to_sleep > 0)
	{
		print_message(watcher, philo, THINK);
		ft_usleep(watcher, watcher->time_to_eat - watcher->time_to_sleep);
	}
}

void	*philo_function(void *arg)
{
	t_watcher	*watcher;
	t_philo		*philo;

	philo = (t_philo *)arg;
	watcher = philo->watcher;
	pthread_mutex_lock(&watcher->lock);
	pthread_mutex_unlock(&watcher->lock);
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
