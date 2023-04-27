/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonghwc <seonghwc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:34:49 by seonghwc          #+#    #+#             */
/*   Updated: 2023/04/27 18:38:41 by seonghwc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/philosopher.h"

void	change_is_full(t_watcher *watcher, int philo_num)
{
	pthread_mutex_lock(&watcher->full_lock);
	watcher->philo_info[philo_num]->is_full = 1;
	pthread_mutex_unlock(&watcher->full_lock);
}

int	get_is_full(t_watcher *watcher, int philo_num)
{
	int	ret;

	pthread_mutex_lock(&watcher->full_lock);
	ret = watcher->philo_info[philo_num]->is_full;
	pthread_mutex_unlock(&watcher->full_lock);
	return (ret);
}
