/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:40:01 by abrun             #+#    #+#             */
/*   Updated: 2021/11/03 18:18:36 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo			*philo;
	int				n_ph;
	int				c;
	struct timeval	time;

	gettimeofday(&time, NULL);
	if (ac < 5)
		return (1);
	c = 0;
	n_ph = ft_atoi(av[1]);
	philo = malloc(sizeof(t_philo) * n_ph);
	if (!philo)
		return (2);
	while (c < n_ph)
	{
		philo[c] = fill_philo_parameters(av);
		philo[c].curr_t = time;
		philo[c].name = ft_strjoin("philo", ft_itoa(c));
		if (!philo[c].name)
			return (3);
		if (pthread_create(&philo[c].thread, NULL, creation, (void *)&philo[c]))
			return (4);
		c++;
	}
	c = 0;
	while (c < n_ph)
	{
		if (pthread_join(philo[c].thread, NULL))
			return (5);
		c++;
	}
	pthread_exit (NULL);
	return (0);
}
