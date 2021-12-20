/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 13:13:39 by abrun             #+#    #+#             */
/*   Updated: 2021/12/20 19:55:49 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_params(t_philo *philo)
{
	t_philo		*next;

	next = philo->next_ph;
	while (next != philo)
	{
		free(next->name);
		free(next->equip);
		pthread_mutex_destroy(&next->fork);
		next = next->next_ph;
	}
	free(next->name);
	free(next->equip);
	pthread_mutex_destroy(&next->fork);
	free(philo[0].g);
	free(philo);
}

void	free_init(t_philo *philo, int c)
{
	int	n;

	n = -1;
	while (++n < c)
	{
		free(philo[n].name);
		pthread_mutex_destroy(&philo[n].fork);
	}
	free(philo[0].g);
	free(philo);
}
