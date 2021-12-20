/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:16:53 by abrun             #+#    #+#             */
/*   Updated: 2021/12/20 19:15:11 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_after_eat(t_philo *philo)
{
	philo->sleep.c = philo->sleep.t;
	philo->sleep.b = 1;
}

void	take_fork(t_philo *philo)
{
	if (!(*philo->equip))
	{
		pthread_mutex_lock(&philo->g->var);
		philo->g->all_m += 1;
		pthread_mutex_unlock(&philo->g->var);
		philo->meal += 1;
	}
	if (*philo->equip != 1 && *philo->equip != 3)
	{
		pthread_mutex_lock(&philo->fork);
		*philo->equip += 1;
		print_msg(philo, "has taken a fork");
		pthread_mutex_unlock(&philo->fork);
	}
	else if (*philo->equip != 2 && *philo->equip != 3)
	{
		pthread_mutex_lock(&philo->next_ph->fork);
		*philo->equip += 2;
		print_msg(philo, "has taken a fork");
		pthread_mutex_unlock(&philo->next_ph->fork);
	}
}
