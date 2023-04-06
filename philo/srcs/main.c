/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 20:07:40 by marvin            #+#    #+#             */
/*   Updated: 2023/03/27 20:07:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../include/philosopher.h"

int	main(int argc, char **argv)
{
	t_watcher	watcher;

	memset(&watcher, 0, sizeof(t_watcher));
	if (argc < 5 || argc > 6)
		return (1);
	if (argc == 5)
		watcher.max_eating = -1;
	initialize_watcher_1(argv, &watcher);
	if (create_philo(&watcher));
		return (1);
}
