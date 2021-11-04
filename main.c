/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:40:01 by abrun             #+#    #+#             */
/*   Updated: 2021/11/04 12:59:43 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo			*philo;
	int				n_ph;
	int				c;
	struct timeval	time;
	int				*ret;

	gettimeofday(&time, NULL);
	if (ac < 5)
		return (1);
	n_ph = ft_atoi(av[1]);
	philo = init_philo(n_ph, av, time);
	if (!philo)
		return (2);
	c = -1;
	while (++c < n_ph)
		if (pthread_create(&philo[c].thread, NULL, creation, (void *)&philo[c]))
			return (4);
	c = -1;
	while (++c < n_ph)
		if (pthread_join(philo[c].thread, (void *)&ret))
			return (5);
	return (0);
}
