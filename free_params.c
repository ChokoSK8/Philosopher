/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 13:13:39 by abrun             #+#    #+#             */
/*   Updated: 2021/11/05 12:08:39 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_params(t_philo *philo)
{
	t_philo		*next;

	next = philo->next;
	while (next != philo)
	{
		free(next->name);
		pthread_mutex_destroy(&next->fork);
		next = next->next;
	}
	free(next->name);
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
