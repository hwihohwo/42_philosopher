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
	pthread_mutex_lock(&watcher->start_lock);
	while (i < watcher->num_of_philo)
	{
		watcher->philo_num = i;
		init_philo(watcher, watcher->philo_info[i]);
		if (pthread_create(&watcher->philo_id[i], NULL, philo_function, \
		(void *)watcher->philo_info[i]))
			return (1);
		i++;
	}
	watcher->start_eating = get_current_time(watcher);
	pthread_mutex_unlock(&watcher->start_lock);
	return (0);
}

void	philo_died(t_watcher *watcher, int philo_num)
{
	int	i;

	i = 0;
	change_someone_died(watcher);
	while (i < watcher->num_of_philo)
		pthread_join(watcher->philo_id[i++], 0);
	print_message(watcher, watcher->philo_info[philo_num], DIE);
	free_watcher(watcher);
}

void	philo_finished(t_watcher *watcher)
{	
	int	i;

	i = 0;
	while (i < watcher->num_of_philo)
		pthread_join(watcher->philo_id[i++], 0);
	free_watcher(watcher);
}

void	watch_philo(t_watcher *watcher)
{
	int	i;
	int	full_philo;
	int	diff;

	full_philo = 0;
	while (1)
	{
		usleep(1000);
		i = 0;
		while (i < watcher->num_of_philo)
		{
			diff = get_current_time(watcher) - get_last_eat(watcher, i);
			if (diff > watcher->time_to_die)
				return (philo_died(watcher, i));
			if (get_is_full(watcher, i) == 1)
			{
				full_philo++;
				change_is_full(watcher, i);
			}
			if (full_philo == watcher->num_of_philo)
				return (philo_finished(watcher));
			i++;
		}
	}
}
