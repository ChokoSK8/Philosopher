/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:30:06 by abrun             #+#    #+#             */
/*   Updated: 2021/11/08 14:29:56 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*creation(void *ptr)
{
	t_philo			*philo;
	struct timeval	t0;
	struct timeval	t1;

	philo = (t_philo *)ptr;
	gettimeofday(&t0, NULL);
	philo->sleep.c = 0;
	while (philo->die.c > 0 && !philo->g->dead && philo->g->meal)
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
		usleep(50);
		t0 = t1;
	}
	if (philo->die.c <= 0 && !philo->g->dead)
	{
		philo->g->dead = 1;
		print_msg(philo, "died");
	}
	return (NULL);
}
