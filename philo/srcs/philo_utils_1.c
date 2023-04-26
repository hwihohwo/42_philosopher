/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 02:03:05 by marvin            #+#    #+#             */
/*   Updated: 2023/03/30 02:03:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/philosopher.h"

void	free_watcher(t_watcher *watcher)
{
	int	i;

	i = 0;
	if (watcher->philo_info != 0)
		while (i < watcher->num_of_philo)
			free(watcher->philo_info[i++]);
	if (watcher->philo_info != 0)
		free(watcher->philo_info);
	if (watcher->philo_id != 0)
		free(watcher->philo_id);
	i = 0;
	while (i < watcher->num_of_philo)
		pthread_mutex_destroy(&watcher->fork[i++]);
	if (watcher->fork != 0)
		free(watcher->fork);
	pthread_mutex_destroy(&watcher->lock);
	pthread_mutex_destroy(&watcher->start_lock);
	pthread_mutex_destroy(&watcher->time_lock);
	pthread_mutex_destroy(&watcher->lasteat_lock);
	pthread_mutex_destroy(&watcher->die_lock);
}

void	error_exit(char *str, t_watcher *watcher)
{
	free_watcher(watcher);
	printf("%s\n", str);
	exit(1);
}

int	get_current_time(t_watcher *watcher)
{
	int	ret1;
	int	ret2;

	pthread_mutex_lock(&watcher->time_lock);
	if (gettimeofday(&watcher->current_time, NULL) == -1)
		error_exit("gettimeofday error", watcher);
	ret1 = (watcher->current_time.tv_usec - watcher->start_time.tv_usec) / 1000;
	ret2 = (watcher->current_time.tv_sec - watcher->start_time.tv_sec) * 1000;
	pthread_mutex_unlock(&watcher->time_lock);
	return (ret1 + ret2);
}

void	print_message(t_watcher *watcher, t_philo *philo, int state)
{
	pthread_mutex_lock(&watcher->lock);
	if (state == FORK)
		printf("%d philo %d has taken a fork\n", \
		get_current_time(watcher), philo->philo_num + 1);
	else if (state == EAT)
		printf("%d philo %d is eating\n", \
		get_current_time(watcher), philo->philo_num + 1);
	else if (state == SLEEP)
		printf("%d philo %d is sleeping\n", \
		get_current_time(watcher), philo->philo_num + 1);
	else if (state == THINK)
		printf("%d philo %d is thinking\n", \
		get_current_time(watcher), philo->philo_num + 1);
	else if (state == DIE)
		printf("%d philo %d died\n", \
		get_current_time(watcher), philo->philo_num + 1);
	pthread_mutex_unlock(&watcher->lock);
}

int	ft_atoi(char *str)
{
	int		i;
	long	ret;
	int		sign;

	ret = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		ret = ret * 10 + (str[i++] - '0');
	if (ret < 0)
		return ((sign + 1) / -2);
	return (sign * ret);
}
