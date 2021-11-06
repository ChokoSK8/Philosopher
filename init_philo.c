/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:47:16 by abrun             #+#    #+#             */
/*   Updated: 2021/11/06 12:25:22 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_philo(int n_ph, int ac, char **av)
{
	int		c;
	t_philo	*philo;
	t_param	*param;
	char	*num;

	philo = malloc(sizeof(t_philo) * n_ph);
	if (!philo)
		return (0);
	param = init_param(ac, av);
	if (!param)
		return (0);
	c = -1;
	while (++c < n_ph)
	{
		philo[c] = fill_philo_parameters(av);
		philo[c].meal = 0;
		num = ft_itoa(c + 1);
		philo[c].name = ft_strjoin("philo", num);
		free(num);
		philo[c].g = param;
		pthread_mutex_init(&philo[c].fork, NULL);
		if (!philo[c].name)
		{
			free_init(philo, c);
			return (0);
		}
		if (c < n_ph - 1)
			philo[c].next = &philo[c + 1];
		else
			philo[c].next = &philo[0];
	}
	c = -1;
	while (++c < n_ph)
	{
		if (c != 0)
			philo[c].prev = &philo[c - 1];
		else
			philo[c].prev = &philo[n_ph - 1];
	}
	return (philo);
}

t_param	*init_param(int ac, char **av)
{
	t_param	*param;

	param = malloc(sizeof(t_param));
	if (!param)
		return (0);
	gettimeofday(&param->start, NULL);
	param->dead = 0;
	pthread_mutex_init(&param->print, NULL);
	if (ac == 6)
		param->meal = ft_atoi(av[1]);
	else
		param->meal = -1;
	if (ac == 6)
		param->n_meal = ft_atoi(av[5]);
	else
		param->n_meal = -1;
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
