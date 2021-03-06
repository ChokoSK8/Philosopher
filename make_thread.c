/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:30:06 by abrun             #+#    #+#             */
/*   Updated: 2021/12/20 19:51:37 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*creation(void *ptr)
{
	t_philo			*philo;

	philo = (t_philo *)ptr;
	gettimeofday(&philo->eat.last, NULL);
	print_msg(philo, "is thinking");
	usleep(100);
	if (philo->id % 2 == 0)
		usleep(100);
	philo->sleep.c = 0;
	while (philo->die.c > 0)
	{
		if (!do_death(philo))
			return (NULL);
		if (philo->die.c > 0 && *philo->equip == 3)
			do_eat(philo);
		else if (philo->sleep.b && philo->die.c > 0)
			do_sleep(philo);
		if (!philo->sleep.b && philo->die.c > 0)
			do_think(philo);
	}
	return (exit_thread(philo));
}

void	*exit_thread(t_philo *philo)
{
	pthread_mutex_lock(&philo->g->end);
	if (philo->die.c <= 0 && !philo->g->dead && philo->g->meal)
	{
		philo->g->dead = 1;
		print_msg(philo, "died");
	}
	pthread_mutex_unlock(&philo->g->end);
	return (NULL);
}
