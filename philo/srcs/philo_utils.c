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
	pthread_mutex_destroy(&watcher->lock);
}

void	error_exit(char *str, t_watcher *watcher)
{
	free_watcher(watcher);
	perror(str);
	exit(1);
}

int	get_current_time(t_watcher *watcher)
{
	if (gettimeofday(&watcher->current_time, NULL) == -1)
		error_exit("gettimeofday:", watcher);
	return (watcher->current_time.tv_usec - watcher->start_time.tv_usec);
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
