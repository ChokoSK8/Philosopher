/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:47:16 by abrun             #+#    #+#             */
/*   Updated: 2021/11/04 18:46:46 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_philo(int n_ph, char **av)
{
	int		c;
	t_philo	*philo;
	t_param	*param;

	philo = malloc(sizeof(t_philo) * n_ph);
	if (!philo)
		return (0);
	param = init_param();
	if (!param)
		return (0);
	c = -1;
	while (++c < n_ph)
	{
		philo[c] = fill_philo_parameters(av);
		philo[c].name = ft_strjoin("philo", ft_itoa(c + 1));
		if (!philo[c].name)
		{
			free(philo);
			return (0);
		}
		pthread_mutex_init(&philo[c].fork, NULL);
		philo[c].g = param;
		if (c < n_ph - 1)
			philo[c].next = &philo[c + 1];
		else
			philo[c].next = &philo[0];
	}
	return (philo);
}

t_param	*init_param(void)
{
	t_param	*param;

	param = malloc(sizeof(t_param));
	if (!param)
		return (0);
	gettimeofday(&param->start, NULL);
	param->dead = 0;
	pthread_mutex_init(&param->print, NULL);
	return (param);
}

t_philo	fill_philo_parameters(char **av)
{
	t_philo	philo;

	philo.sleep.t = ft_atoi(av[4]);
	philo.sleep.c = ft_atoi(av[4]);
	philo.sleep.b = 0;
	philo.eat.t = ft_atoi(av[3]);
	philo.eat.c = ft_atoi(av[3]);
	philo.eat.b = 0;
	philo.die.t = ft_atoi(av[2]);
	philo.die.c = ft_atoi(av[2]);
	philo.think = 0;
	philo.equip = 0;
	return (philo);
}
