/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghwc <seonghwc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:28:39 by seonghwc          #+#    #+#             */
/*   Updated: 2023/04/26 13:31:11 by seonghwc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/philosopher.h"

void	change_last_eat(t_watcher *watcher, int philo_num, int value)
{
	pthread_mutex_lock(&watcher->lasteat_lock);
	watcher->philo_info[philo_num]->last_eat = value;
	pthread_mutex_unlock(&watcher->lasteat_lock);
}

int	get_last_eat(t_watcher *watcher, int philo_num)
{
	int	ret;

	pthread_mutex_lock(&watcher->lasteat_lock);
	ret = watcher->philo_info[philo_num]->last_eat;
	pthread_mutex_unlock(&watcher->lasteat_lock);
	return (ret);
}

void	change_someone_died(t_watcher *watcher)
{
	pthread_mutex_lock(&watcher->die_lock);
	watcher->someone_died = 1;
	pthread_mutex_unlock(&watcher->die_lock);
}

int	get_someone_died(t_watcher *watcher)
{
	int	ret;

	pthread_mutex_lock(&watcher->die_lock);
	ret = watcher->someone_died;
	pthread_mutex_unlock(&watcher->die_lock);
	return (ret);
}
