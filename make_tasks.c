/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tasks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:31:16 by abrun             #+#    #+#             */
/*   Updated: 2021/12/15 21:48:45 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	do_death(t_philo *philo)
{
	struct timeval	t1;

	pthread_mutex_lock(&philo->g->end);
	if (philo->g->dead || !philo->g->meal)
	{
		pthread_mutex_unlock(&philo->g->end);
		return (0);
	}
	pthread_mutex_unlock(&philo->g->end);
	gettimeofday(&t1, NULL);
	if (ft_diff_time(philo->eat.last, t1) >= philo->die.t)
		philo->die.c = 0;
	return (1);
}

void	do_eat(t_philo *philo)
{
	philo->die.c = philo->die.t - philo->eat.t;
	print_msg(philo, "is eating");
	philo->eat.b = 1;
	gettimeofday(&philo->eat.last, NULL);
	if (!ft_timer(philo->eat.t, philo->eat.last, philo))
		philo->die.c = 0;
	set_after_eat(philo);
	pthread_mutex_lock(&philo->g->end);
	if (philo->meal == philo->g->n_meal && philo->g->meal)
		philo->g->meal--;
	pthread_mutex_unlock(&philo->g->end);
}

void	do_sleep(t_philo *philo)
{
	struct timeval	t1;

	print_msg(philo, "is_sleeping");
	philo->sleep.b = 0;
	gettimeofday(&t1, NULL);
	if (!ft_timer(philo->sleep.t, t1, philo))
		philo->die.c = 0;
	philo->eat.c = philo->eat.t;
	philo->eat.b = 0;
}

void	do_think(t_philo *philo)
{
	struct timeval	t;

	if (philo->think)
		print_msg(philo, "is thinking");
	philo->think = 1;
	while (philo->equip != 3)
	{
		pthread_mutex_lock(&philo->g->think);
		if (!philo->next->equip && !philo->prev->equip
			&& (can_he_eats(philo->meal, philo->g)
				|| philo->equip))
		{
			take_fork(philo);
		}
		pthread_mutex_unlock(&philo->g->think);
		usleep(50);
		gettimeofday(&t, NULL);
		if (ft_diff_time(philo->eat.last, t) >= philo->die.t)
		{
			philo->die.c = 0;
			return;
		}
	}
}
