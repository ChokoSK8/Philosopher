/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tasks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:31:16 by abrun             #+#    #+#             */
/*   Updated: 2021/11/10 15:20:41 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	do_death(t_philo *philo, struct timeval t0)
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
	philo->die.c -= ft_diff_time(t0, t1);
	return (1);
}

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
		set_after_eat(philo);
		pthread_mutex_lock(&philo->g->end);
		if (philo->meal == philo->g->n_meal && philo->g->meal)
			philo->g->meal--;
		pthread_mutex_unlock(&philo->g->end);
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
	pthread_mutex_lock(&philo->g->think);
	if (!philo->next->equip && !philo->prev->equip
		&& (can_he_eats(philo->meal, philo->g)
			|| philo->equip))
	{
		take_fork(philo);
	}
	else if (!philo->think)
	{
		print_msg(philo, "is thinking");
		philo->think = 1;
	}
	pthread_mutex_unlock(&philo->g->think);
}
