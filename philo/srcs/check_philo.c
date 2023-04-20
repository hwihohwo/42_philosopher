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
		usleep(10);
	}
	gettimeofday(&watcher->start_time, 0);
	pthread_mutex_unlock(&watcher->lock);
	return (0);
}

void	philo_died(t_watcher *watcher, int philo_num)
{
	int	i;

	i = 0;
	while (i < watcher->num_of_philo)
		pthread_detach(watcher->philo_id[i++]);
	print_message(watcher, watcher->philo_info[philo_num], DIE);
	free_watcher(watcher);
	exit(0);
}

void	philo_finished(t_watcher *watcher)
{
	int	i;

	i = 0;
	free_watcher(watcher);
	while (i < watcher->num_of_philo)
		pthread_join(watcher->philo_id[i++], 0);
	exit(0);
}

int	watch_philo(t_watcher *watcher)
{
	int	i;
	int	full_philo;
	int	diff;

	full_philo = 0;
	while (1)
	{
		i = 0;
		while (i < watcher->num_of_philo)
		{
			diff = get_current_time(watcher) - watcher->philo_info[i]->last_eat;
			if (diff > watcher->time_to_die)
				philo_died(watcher, i);
			if (watcher->max_eating != -1)
				if (watcher->philo_info[i]->is_full == 1)
					full_philo++;
			if (full_philo == watcher->num_of_philo)
				philo_finished(watcher);
			i++;
		}
	}
}
