/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tasks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:31:16 by abrun             #+#    #+#             */
/*   Updated: 2021/12/20 19:44:15 by abrun            ###   ########.fr       */
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
	pthread_mutex_lock(&philo->g->think);
	*philo->equip = 0;
	pthread_mutex_unlock(&philo->g->think);
	set_after_eat(philo);
	pthread_mutex_lock(&philo->g->end);
	if (philo->meal == philo->g->n_meal && philo->g->meal)
	{
		philo->g->meal--;
		if (!philo->g->meal)
			philo->die.c = 0;
	}
	pthread_mutex_unlock(&philo->g->end);
}

void	do_sleep(t_philo *philo)
{
	struct timeval	t1;

	pthread_mutex_lock(&philo->g->think);
	*philo->equip = 0;
	pthread_mutex_unlock(&philo->g->think);
	print_msg(philo, "is sleeping");
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
	while (*philo->equip != 3)
	{
		timer(1);
		pthread_mutex_lock(&philo->g->think);
		if (!(*philo->next) && !(*philo->prev))
		{
			if ((*philo->equip || can_he_eats(philo, philo->g)))
			{
				take_fork(philo);
			}
		}
		pthread_mutex_unlock(&philo->g->think);
		gettimeofday(&t, NULL);
		if (ft_diff_time(philo->eat.last, t) >= philo->die.t)
		{
			philo->die.c = 0;
			return ;
		}
	}
}
