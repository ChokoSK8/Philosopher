/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:40:01 by abrun             #+#    #+#             */
/*   Updated: 2021/12/20 19:36:43 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo			*philo;
	int				n_ph;
	int				c;

	if (check_error(ac, av))
		return (1);
	n_ph = ft_atoi(av[1]);
	philo = init_philo(n_ph, ac, av);
	if (!philo)
		return (2);
	c = -1;
	while (++c < n_ph)
	{
		if (pthread_create(&philo[c].thread, NULL, creation, (void *)&philo[c]))
			return (4);
	}
	c = -1;
	while (++c < n_ph)
	{
		if (pthread_join(philo[c].thread, NULL))
			return (5);
	}
	free_params(philo);
	return (0);
}
