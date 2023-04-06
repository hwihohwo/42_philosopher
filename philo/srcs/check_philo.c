/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:50:38 by marvin            #+#    #+#             */
/*   Updated: 2023/03/30 17:50:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/philosopher.h"

int	create_philo(t_watcher *watcher)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&watcher->lock);
	while (i < watcher->num_of_philo)
	{
		watcher->philo_num = i;
		if (pthread_create(&watcher->philo_id[i], NULL, philo_function, \
		(void *)watcher))
			return (1);
		i++;
	}
	pthread_mutex_unlock(&watcher->lock);
	return (0);
}

int	watch_philo(t_watcher *watcher)
{
	int	i;

	while (1)
	{
		i = 0;
		usleep(5);
		while (watcher->philo_info[i]->)
	}
}
