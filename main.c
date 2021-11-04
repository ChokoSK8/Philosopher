/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:40:01 by abrun             #+#    #+#             */
/*   Updated: 2021/11/04 17:37:21 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo			*philo;
	int				n_ph;
	int				c;

	if (ac < 5)
		return (1);
	n_ph = ft_atoi(av[1]);
	philo = init_philo(n_ph, av);
	if (!philo)
		return (2);
	c = -1;
	while (++c < n_ph)
	{
		if (pthread_create(&philo[c].thread, NULL, creation, (void *)&philo[c]))
			return (4);
		if (pthread_detach(philo[c].thread))
			return (5);
	}
	pthread_exit(NULL);
	return (0);
}
