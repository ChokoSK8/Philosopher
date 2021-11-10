/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:47:16 by abrun             #+#    #+#             */
/*   Updated: 2021/11/10 13:51:35 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_philo(int n_ph, int ac, char **av)
{
	int		c;
	t_philo	*philo;
	t_param	*param;

	philo = malloc(sizeof(t_philo) * n_ph);
	if (!philo)
		return (0);
	param = init_param(ac, av, n_ph);
	if (!param)
		return (0);
	c = -1;
	while (++c < n_ph)
	{
		philo[c] = fill_philo_parameters(av, c, param);
		if (!philo[c].name)
		{
			free_init(philo, c);
			return (0);
		}
	}
	c = -1;
	while (++c < n_ph)
		philo = assign_prev_next(philo, c, n_ph);
	return (philo);
}

t_param	*init_param(int ac, char **av, int n_ph)
{
	t_param	*param;

	param = malloc(sizeof(t_param));
	if (!param)
		return (0);
	gettimeofday(&param->start, NULL);
	param->dead = 0;
	pthread_mutex_init(&param->print, NULL);
	pthread_mutex_init(&param->var, NULL);
	pthread_mutex_init(&param->think, NULL);
	pthread_mutex_init(&param->end, NULL);
	if (ac == 6)
		param->meal = n_ph;
	else
		param->meal = -1;
	if (ac == 6)
		param->n_meal = ft_atoi(av[5]);
	else
		param->n_meal = -1;
	param->n_ph = n_ph;
	param->all_m = 0;
	return (param);
}

t_philo	fill_philo_parameters(char **av, int c, t_param *param)
{
	t_philo	philo;
	char	*num;

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
	philo.meal = 0;
	num = ft_itoa(c + 1);
	philo.name = ft_strjoin("philo", num);
	free(num);
	philo.g = param;
	pthread_mutex_init(&philo.fork, NULL);
	return (philo);
}

t_philo	*assign_prev_next(t_philo *philo, int c, int n_ph)
{
	if (n_ph > 1)
	{
		if (c < n_ph - 1)
			philo[c].next = &philo[c + 1];
		else
			philo[c].next = &philo[0];
		if (c != 0)
			philo[c].prev = &philo[c - 1];
		else
			philo[c].prev = &philo[n_ph - 1];
	}
	else
	{
		philo[c].prev = &philo[c];
		philo[c].next = &philo[c];
	}
	return (philo);
}
