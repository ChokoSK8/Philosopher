/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tasks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:31:16 by abrun             #+#    #+#             */
/*   Updated: 2021/11/05 11:44:13 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	do_eat(struct timeval t0, t_philo *philo)
{
	struct timeval	t1;

	if (!philo->eat.b)
	{
		philo->die.c = philo->die.t;
		philo->think = 0;
		print_msg(philo, "is eating");
		philo->eat.b = 1;
	}
	else
	{
		gettimeofday(&t1, NULL);
		philo->eat.c -= ft_diff_time(t0, t1);
	}
	if (philo->eat.c <= 0)
	{
		philo->sleep.c = philo->sleep.t;
		philo->sleep.b = 0;
		philo->equip = 0;
		philo->meal += 1;
		usleep(100);
		if (philo->meal == philo->g->n_meal && philo->g->meal)
			philo->g->meal--;
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
	}
}

void	do_sleep(struct timeval t0, t_philo *philo)
{
	struct timeval	t1;

	if (!philo->sleep.b)
	{
		print_msg(philo, "is_sleeping");
		philo->sleep.b = 1;
	}
	else
	{
		gettimeofday(&t1, NULL);
		philo->sleep.c -= ft_diff_time(t0, t1);
	}
	if (philo->sleep.c <= 0)
	{
		philo->eat.c = philo->eat.t;
		philo->eat.b = 0;
	}
}

void	do_think(t_philo *philo)
{
	usleep(100);
	if (philo->equip != 1 && !philo->next->equip && !philo->prev->equip)
	{
		philo->equip = 1;
		pthread_mutex_lock(&philo->fork);
		print_msg(philo, "has taken a fork");
	}
	else if (philo->equip != 2 && philo->equip != 3
		&& !philo->next->equip && !philo->prev->equip)
	{
		philo->equip += 2;
		pthread_mutex_lock(&philo->next->fork);
		print_msg(philo, "has taken a fork");
	}
	else if (!philo->think)
	{
		print_msg(philo, "is thinking");
		philo->think = 1;
	}
}
