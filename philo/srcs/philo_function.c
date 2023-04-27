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
	int	diff;

	dest = get_current_time(watcher) + milsec;
	while (get_someone_died(watcher) == 0)
	{
		diff = dest - get_current_time(watcher);
		if (diff <= 0)
			break ;
		else if (diff < milsec)
			usleep(milsec - diff);
		else
			usleep(milsec * 200);
	}
}

void	init_philo(t_watcher *watcher, t_philo *philo)
{
	philo->philo_num = watcher->philo_num;
	philo->num_of_eat = 0;
	philo->is_full = 0;
	change_last_eat(watcher, philo->philo_num, watcher->start_eating);
	philo->watcher = watcher;
}

void	get_fork_and_eat(t_watcher *watcher, t_philo *philo)
{
	pthread_mutex_lock(&watcher->fork[philo->philo_num]);
	print_message(watcher, philo, FORK);
	pthread_mutex_lock(&watcher->fork[(philo->philo_num + 1) \
	% watcher->num_of_philo]);
	print_message(watcher, philo, FORK);
	change_last_eat(watcher, philo->philo_num, get_current_time(watcher));
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
	pthread_mutex_lock(&watcher->start_lock);
	pthread_mutex_unlock(&watcher->start_lock);
	if (philo->philo_num % 2 == 1)
		ft_usleep(watcher, watcher->time_to_eat / 2);
	while (philo->is_full == 0 && get_someone_died(watcher) == 0)
	{
		if (philo->is_full == 0 && get_someone_died(watcher) == 0 && \
		watcher->num_of_philo != 1)
			get_fork_and_eat(watcher, philo);
		if (philo->num_of_eat == watcher->max_eating)
		{
			philo->is_full = 1;
			break ;
		}
		if (philo->is_full == 0 && get_someone_died(watcher) == 0 && \
		watcher->num_of_philo != 1)
			sleep_and_think(watcher, philo);
	}
	return (0);
}
