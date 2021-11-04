/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:30:06 by abrun             #+#    #+#             */
/*   Updated: 2021/11/04 18:33:45 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*creation(void *ptr)
{
	t_philo			*philo;
	struct timeval	t0;
	struct timeval	t1;

	philo = (t_philo *)ptr;
	usleep(50000);
	gettimeofday(&t0, NULL);
	philo->sleep.c = 0;
	while (philo->die.c > 0 && !philo->g->dead)
	{
		gettimeofday(&t1, NULL);
		philo->die.c -= ft_diff_time(t0, t1);
		if (philo->eat.c > 0 && philo->die.c > 0 && philo->equip == 3)
			do_eat(t0, philo);
		else if (philo->sleep.c > 0 && philo->die.c > 0)
			do_sleep(t0, philo);
		if (philo->sleep.c <= 0 && !philo->eat.b
			&& philo->die.c > 0)
			do_think(philo);
		usleep(1000);
		t0 = t1;
	}
	if (philo->die.c <= 0 && !philo->g->dead)
	{
		philo->g->dead = 1;
		pthread_mutex_lock(&philo->g->print);
		gettimeofday(&t0, NULL);
		philo->die.c = ft_diff_time(philo->g->start, t0);
		printf("\033[0;37m");
		printf("\n%ld %s died\n", philo->die.c, philo->name);
		pthread_mutex_unlock(&philo->g->print);
	}
	usleep(1000);
	free(philo->name);
	return (NULL);
}
